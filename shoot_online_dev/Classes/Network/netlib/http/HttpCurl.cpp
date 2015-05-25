#include "HttpCurl.h"
#include "curl/curl.h"

namespace scnet
{

static int writer(char *data, size_t size, size_t nmemb, std::string *res)
{    
    if (res != NULL)  
    {
        res->append(data, size * nmemb);
        return size * nmemb;  
    }
    
    return 0;
}

bool HttpCurl::get(const std::string &url, std::string &res, int timeout)
{
    CURL *curl = curl_easy_init();
    if (!curl) return false;
//    struct curl_slist *headers = NULL;
//    curl_slist_append(headers, "Accept: */*");  
//    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_ENCODING, "deflate,gzip");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
    
    CURLcode retcode = curl_easy_perform(curl);
//    curl_slist_free_all(headers);
    
    if (CURLE_OK == retcode) 
    {
        long responseCode = 0;
        retcode = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        if ((CURLE_OK == retcode) && responseCode>=200 && responseCode<300)
        {
            curl_easy_cleanup(curl);
            return true;
        }
    }
    
    curl_easy_cleanup(curl);
    return false;    
}

bool HttpCurl::post(const std::string &url, const std::string &req, std::string &res, int timeout)
{
    CURL *curl = curl_easy_init();
    if (!curl) return false;
//    struct curl_slist *headers = NULL;
//    curl_slist_append(headers, "Accept: */*");  
//    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_ENCODING, "deflate,gzip");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, req.size());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
    
    CURLcode retcode = curl_easy_perform(curl);
//    curl_slist_free_all(headers);
    
    if (CURLE_OK == retcode) 
    {        
        long responseCode = 0;
        retcode = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        if ((CURLE_OK == retcode) && responseCode>=200 && responseCode<300)
        {
            curl_easy_cleanup(curl);
            return true;
        }
    }
    
    curl_easy_cleanup(curl);
    return false;
}

}
