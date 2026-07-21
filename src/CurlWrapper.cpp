#include "llm/CurlWrapper.hpp"

bool CURL_INITED = false;

/*
 * Only constructor for class
 *
 * Initializes private variables and globally inits cURL (if not already inited)
 * Errors are returned as error strings, error arg expected to be empty
 */
CurlWrapper::CurlWrapper() {
  if (!CURL_INITED) {
    curl_global_init(CURL_GLOBAL_SSL); // initialize cURL and SSL
  }
}

CurlWrapper::~CurlWrapper() {
  if (CURL_INITED) {
    curl_global_cleanup();
  }
}

/*
 * Easily send a request using a URL, headers, and a write callback function
 * 
 * Any cURL errors will load the error message into the error string, which is expected to be empty
 * 
 * Returns the HTTP return code, or -1 if there was a cURL error
 */
long CurlWrapper::sendRequest(
  const std::string& url,
  const std::unordered_map<std::string, std::string>& headers,
  const json& body,
  size_t (*write_data)(char* buffer, size_t size, size_t nmemb, void* userp),
  std::string& error
) {
  CURL* handle = curl_easy_init(); // create the interface for the HTTP call

  curl_easy_setopt(handle, CURLOPT_URL, url.c_str()); // add the URL to call

  // create the headers
  struct curl_slist* header_list = nullptr;
  for (const auto& pair : headers) {
    const std::string header = pair.first + ": " + pair.second;
    header_list = curl_slist_append(header_list, header.c_str());
  }
  curl_easy_setopt(handle, CURLOPT_HTTPHEADER, header_list);

  // add the JSON body
  const std::string json_string = body.dump();
  curl_easy_setopt(handle, CURLOPT_POSTFIELDS, json_string.c_str());
  curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, json_string.size());
  
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data); // add the custom callback to write received data

  // set up the error system
  std::vector<char> err(CURL_ERROR_SIZE);
  curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, err.data());
  
  CURLcode success = curl_easy_perform(handle); // actually make the call

  // retrieve HTTP code
  long code;
  curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &code);
  
  curl_slist_free_all(header_list);
  curl_easy_cleanup(handle); // free all resources

  if (success != CURLE_OK) {
    error = std::string(err.begin(), err.end());
    return -1;
  }

  return code;
}