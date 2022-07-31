#define _CRT_SECURE_NO_WANINGS
#define CURL_STATICLIB

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "search.h"
#include "curl/curl.h"
#include "json/json.h"
#include "iconv.h"


char* servicekey1(void) {
	std::string apiKey1 = "여기에 서비스키를 입력하세요(type your service key) [https://www.data.go.kr/data/15073877/openapi.do]"; 
	std::string param_apikey1 = "servicekey=" + apiKey1;
    static char ch_apiKey1[256];
    strcpy_s(ch_apiKey1, param_apikey1.c_str());
    return ch_apiKey1;
}


char* servicekey2(void) {
	std::string apiKey2 = "여기에 서비스키를 입력하세요(type your service key) [https://www.data.go.kr/data/15073861/openapi.do]"; 
	std::string param_apikey2 = "servicekey=" + apiKey2;
    static char ch_apiKey2[256];
    strcpy_s(ch_apiKey2, param_apikey2.c_str());
    return ch_apiKey2;
}


// UrlEncode Function
std::string UrlEncode(const std::string& s)
{
    const std::string unreserved = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~";

    std::string escaped = "";
    for (size_t i = 0; i < s.length(); i++)
    {
        if (unreserved.find_first_of(s[i]) != std::string::npos)
        {
            escaped.push_back(s[i]);
        }
        else
        {
            escaped.append("%");
            char buf[3];
            sprintf_s(buf, "%.2X", (unsigned char)s[i]);
            escaped.append(buf);
        }
    }

    return escaped;
}


// Iconv를 활용한 UTF-8 <-> cp949 encoding Function
char* encoding(char* text_input, const char* source, const char* target)
{
    iconv_t it;
    int input_len = strlen(text_input) + 1;
    int output_len = input_len * 2;
    size_t in_size = input_len;
    size_t out_size = output_len;
    char* output = (char*)malloc(output_len);
    char* output_buf = output;
    char* input_buf = text_input;
    it = iconv_open(target, source);
    int ret = iconv(it, &input_buf, &in_size, &output_buf, &out_size);
    iconv_close(it);

    return output;
}


// cp949 -> UTF-8 -> URLEncode Function
std::string kor2url(char* text_input)
{
    const char* utf8 = "UTF-8";
    const char* cp949 = "cp949";
    char* text_utf8 = encoding(text_input, cp949, utf8);
    char* text_cp949 = encoding(text_utf8, utf8, cp949);
    std::string str_utf8 = text_utf8;
    std::string str_url;
    str_url = UrlEncode(str_utf8);

    return str_url;
}


//libcurl Reader Function
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    
    return size * nmemb;
}


// open Api에서 tmX parse
char* parse_tmX(std::string x_placePercent) 
{   
    // Create URL
    CURL* curl;
    CURLcode res;

    CURLU* urlp1;
    CURLUcode uc;

    std::string readBuffer;

    char* urlX;

    curl = curl_easy_init();
    urlp1 = curl_url();
    uc = curl_url_set(urlp1, CURLUPART_URL, "https://apis.data.go.kr/B552584/MsrstnInfoInqireSvc/getTMStdrCrdnt?", 0);

    if (!uc) 
    {   
        //create paramters
        char ch[100];
        strcpy_s(ch, x_placePercent.c_str());
        char umd[100] = "umdName=";
        strcat_s(umd, ch);

        // Add paramters
        uc = curl_url_set(urlp1, CURLUPART_QUERY, servicekey1(), CURLU_APPENDQUERY);
        uc = curl_url_set(urlp1, CURLUPART_QUERY, "returnType=json&numOfRows=100&pageNo=1", CURLU_APPENDQUERY);
        uc = curl_url_set(urlp1, CURLUPART_QUERY, umd, CURLU_APPENDQUERY);
        
        // Convert URL to string for printing
        uc = curl_url_get(urlp1, CURLUPART_URL, &urlX, 0);
    }

    if (curl)
    {
        /* set urlp to use as working URL */
        curl_easy_setopt(curl, CURLOPT_CURLU, urlp1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        goto cleanup;
    }

cleanup:
    curl_url_cleanup(urlp1);
    curl_easy_cleanup(curl);

    Json::Reader reader;
    Json::Value obj;
    reader.parse(readBuffer, obj);

    int iCount;
    if (obj.get("response", "").isObject()) // Object 확인 
    {
        iCount = obj.get("response", "").get("body", "").get("totalCount", "").asInt();
    }

    Json::Value obj1 = obj.get("response", "").get("body", "")["items"];

    std::string x = obj1[0].get("tmX", "").asString();
    std::string x_tm = "tmX=";
    std::string strX;
    strX = "tmX=" + x;

    static char chX[20];
    strcpy_s(chX,strX.c_str());

    return chX;
}


// open Api에서 tmY parse
char* parse_tmY(std::string x_placePercent) 
{
    // Create URL
    CURL* curl;
    CURLcode res;

    CURLU* urlp2;
    CURLUcode uc;

    std::string readBuffer;

    char* urlY;

    curl = curl_easy_init();
    urlp2 = curl_url();
    uc = curl_url_set(urlp2, CURLUPART_URL, "https://apis.data.go.kr/B552584/MsrstnInfoInqireSvc/getTMStdrCrdnt?", 0);

    if (!uc) 
    {
        // create paramters
        char ch[100];
        strcpy_s(ch, x_placePercent.c_str());
        char umd[100] = "umdName=";
        strcat_s(umd, ch);

        // Add paramters
        uc = curl_url_set(urlp2, CURLUPART_QUERY, servicekey1(), CURLU_APPENDQUERY);
        uc = curl_url_set(urlp2, CURLUPART_QUERY, "returnType=json&numOfRows=100&pageNo=1", CURLU_APPENDQUERY);
        uc = curl_url_set(urlp2, CURLUPART_QUERY, umd, CURLU_APPENDQUERY);

        // Convert URL to string for printing
        uc = curl_url_get(urlp2, CURLUPART_URL, &urlY, 0);
    }

    if (curl) 
    {
        /* set urlp to use as working URL */
        curl_easy_setopt(curl, CURLOPT_CURLU, urlp2);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        goto cleanup;
    }

cleanup:
    curl_url_cleanup(urlp2);
    curl_easy_cleanup(curl);

    Json::Reader reader;
    Json::Value obj;
    reader.parse(readBuffer, obj);

    int iCount;
    if (obj.get("response", "").isObject()) // Object 확인 
    {
        iCount = obj.get("response", "").get("body", "").get("totalCount", "").asInt();
    }

    Json::Value obj1 = obj.get("response", "").get("body", "")["items"];

    std::string y = obj1[0].get("tmY", "").asString();
    std::string y_tm = "tmY=";
    std::string strY;
    strY = y_tm + y;

    static char chY[20];
    strcpy_s(chY,strY.c_str());

    return chY;
}


// 현위치의 tmx tmy 좌표로 가장 가까운 관측소 검색
std::string herePlace(std::string x_placePercent) 
{      
    // Create URL
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    CURLU* urlp3;
    CURLUcode uc;
    char* urlxy;
    curl = curl_easy_init();

    urlp3 = curl_url();

    uc = curl_url_set(urlp3, CURLUPART_URL, "https://apis.data.go.kr/B552584/MsrstnInfoInqireSvc/getNearbyMsrstnList?", 0);

    if (!uc) 
    {
        // Add paramters
        uc = curl_url_set(urlp3, CURLUPART_QUERY, servicekey1(), CURLU_APPENDQUERY);
        uc = curl_url_set(urlp3, CURLUPART_QUERY, "returnType=json", CURLU_APPENDQUERY);

        uc = curl_url_set(urlp3, CURLUPART_QUERY, parse_tmX(x_placePercent), CURLU_APPENDQUERY);
        uc = curl_url_set(urlp3, CURLUPART_QUERY, parse_tmY(x_placePercent), CURLU_APPENDQUERY);

        // Convert URL to string for printing
        uc = curl_url_get(urlp3, CURLUPART_URL, &urlxy, 0);
    }

    if (curl) 
    {
        /* set urlp to use as working URL */
        curl_easy_setopt(curl, CURLOPT_CURLU, urlp3);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        goto cleanup;
    }

    cleanup:
    curl_url_cleanup(urlp3);
    curl_easy_cleanup(curl);


    Json::Reader reader;
    Json::Value obj;
    reader.parse(readBuffer, obj);

    Json::Value obj1 = obj.get("response", "").get("body", "")["items"];
    std::string asciiStation = obj1[0].get("stationName", "").asString();

    int len = strlen(asciiStation.c_str()) + 1;
    WCHAR outName[MAX_PATH];
    char scan_stationName[MAX_PATH];
    WCHAR* wChar = new WCHAR[len];
    wChar[0] = 0;
    MultiByteToWideChar(CP_UTF8, 0, asciiStation.c_str(), len, wChar, len);
    WideCharToMultiByte(CP_ACP, 0, wChar, len, scan_stationName, len, 0, 0);
    delete[] wChar;

    return scan_stationName;
}

// 관측소의 주소 parse
std::string adress(std::string x_placePercent) 
{
    // Create URL
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    CURLU* urlp4;
    CURLUcode uc;
    char* urlAd;
    curl = curl_easy_init();

    urlp4 = curl_url();

    uc = curl_url_set(urlp4, CURLUPART_URL, "https://apis.data.go.kr/B552584/MsrstnInfoInqireSvc/getNearbyMsrstnList?", 0);

    if (!uc)
    {
        // Add paramters
        uc = curl_url_set(urlp4, CURLUPART_QUERY, servicekey1(), CURLU_APPENDQUERY);
        uc = curl_url_set(urlp4, CURLUPART_QUERY, "returnType=json&numOfRows=100&pageNo=1", CURLU_APPENDQUERY);
        uc = curl_url_set(urlp4, CURLUPART_QUERY, parse_tmX(x_placePercent), CURLU_APPENDQUERY);
        uc = curl_url_set(urlp4, CURLUPART_QUERY, parse_tmY(x_placePercent), CURLU_APPENDQUERY);

        // Convert URL to string for printing
        uc = curl_url_get(urlp4, CURLUPART_URL, &urlAd, 0);
    }


    if (curl)
    {
        /* set urlp to use as working URL */
        curl_easy_setopt(curl, CURLOPT_CURLU, urlp4);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        goto cleanup;
    }
cleanup:
    curl_url_cleanup(urlp4);
    curl_easy_cleanup(curl);


    Json::Reader reader;
    Json::Value obj;
    reader.parse(readBuffer, obj);

    Json::Value obj1 = obj.get("response", "").get("body", "")["items"];
    std::string adressStation = obj1[0].get("addr", "").asString();

    int len = strlen(adressStation.c_str()) + 1;
    WCHAR outName[MAX_PATH];
    char scan_adress[MAX_PATH];
    WCHAR* wChar = new WCHAR[len];
    wChar[0] = 0;
    MultiByteToWideChar(CP_UTF8, 0, adressStation.c_str(), len, wChar, len);
    WideCharToMultiByte(CP_ACP, 0, wChar, len, scan_adress, len, 0, 0);
    delete[] wChar;

    return scan_adress;
}


// 가장 가까운 관측소와 현위치의 거리
float km(std::string x_placePercent)
{
    // Create URL
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    CURLU* urlp5;
    CURLUcode uc;
    char* urlkm;
    curl = curl_easy_init();

    urlp5 = curl_url();

    uc = curl_url_set(urlp5, CURLUPART_URL, "https://apis.data.go.kr/B552584/MsrstnInfoInqireSvc/getNearbyMsrstnList", 0);

    if (!uc) 
    {
        // Add paramters
        uc = curl_url_set(urlp5, CURLUPART_QUERY, servicekey1(), CURLU_APPENDQUERY);
        uc = curl_url_set(urlp5, CURLUPART_QUERY, "returnType=json&numOfRows=100&pageNo=1", CURLU_APPENDQUERY);
        uc = curl_url_set(urlp5, CURLUPART_QUERY, parse_tmX(x_placePercent), CURLU_APPENDQUERY);
        uc = curl_url_set(urlp5, CURLUPART_QUERY, parse_tmY(x_placePercent), CURLU_APPENDQUERY);

        // Convert URL to string for printing
        uc = curl_url_get(urlp5, CURLUPART_URL, &urlkm, 0);
    }


    if (curl) 
    {
        /* set urlp to use as working URL */
        curl_easy_setopt(curl, CURLOPT_CURLU, urlp5);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        goto cleanup;
    }

    cleanup:
    curl_url_cleanup(urlp5);
    curl_easy_cleanup(curl);

    Json::Reader reader;
    Json::Value obj;
    reader.parse(readBuffer, obj);

    Json::Value obj1 = obj.get("response", "").get("body", "")["items"];
    float distance = obj1[0].get("tm", "").asFloat();

    return distance;
}


// main function
int search(char privatePlace[20]) 
{   
    std::string place_percent = kor2url(privatePlace);

    std::string observer_location = herePlace(place_percent);

    // Create URL
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    CURLU* urlp;
    CURLUcode uc;
    char* url;
    curl = curl_easy_init();

    urlp = curl_url();

    uc = curl_url_set(urlp, CURLUPART_URL, "https://apis.data.go.kr/B552584/ArpltnInforInqireSvc/getCtprvnRltmMesureDnsty?", 0);
    
    if (!uc) 
    {
        // Add paramters
        uc = curl_url_set(urlp, CURLUPART_QUERY, servicekey2(), CURLU_APPENDQUERY);
        uc = curl_url_set(urlp, CURLUPART_QUERY, "&returnType=json&numOfRows=1000&pageNo=1&sidoName=%EC%A0%84%EA%B5%AD&ver=1.0", CURLU_APPENDQUERY);
 
        // Convert URL to string for printing
        uc = curl_url_get(urlp, CURLUPART_URL, &url, 0);
    }


    if (curl) 
    {
        /* set urlp to use as working URL */
        curl_easy_setopt(curl, CURLOPT_CURLU, urlp);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        goto cleanup;
    }

    cleanup:
    curl_url_cleanup(urlp);
    curl_easy_cleanup(curl);


    Json::Reader reader;
    Json::Value obj;
    reader.parse(readBuffer, obj);

    int iCount;
    if (obj.get("response", "").isObject()) // Object 확인 
    {
        iCount = obj.get("response", "").get("body", "").get("totalCount", "").asInt();

    }

    Json::Value obj1 = obj.get("response", "").get("body", "")["items"];
    for (int iLoop = 0; iLoop < iCount; iLoop++) 
    {
        std::string asciiStation = obj1[iLoop].get("stationName", "").asString();

        int len = strlen(asciiStation.c_str()) + 1;
        WCHAR outName[MAX_PATH];
        char stationName[MAX_PATH];
        WCHAR* wChar = new WCHAR[len];
        wChar[0] = 0;
        MultiByteToWideChar(CP_UTF8, 0, asciiStation.c_str(), len, wChar, len);
        WideCharToMultiByte(CP_ACP, 0, wChar, len, stationName, len, 0, 0);
        delete[] wChar;

        if (observer_location == stationName) 
        {
            std::cout << std::endl << "현위치 : " << privatePlace << std::endl << std::endl;
            std::cout << "현위치에서 가장 가까운 관측소는 [" << stationName << "관측소] 입니다." << std::endl;
            std::cout << "[" << stationName << "관측소] 주소 : " << adress(place_percent) << std::endl;
            std::cout << "현위치와 관측소의 거리 : " << km(place_percent) << "km" << std::endl << std::endl;

            std::cout << "오존 농도(O3)          : " << obj1[iLoop].get("o3Value", "").asString() << std::endl;
            std::cout << "미세먼지 농도(PM10)    : " << obj1[iLoop].get("pm10Value", "").asString() << std::endl;
            std::cout << "초미세먼지 농도(PM2.5) : " << obj1[iLoop].get("pm25Value", "").asString() << std::endl << std::endl;

            std::cout << "측정시간 : " << obj1[iLoop].get("dataTime", "").asString() << std::endl;

            break;
        }
    }

    return 0;
}
