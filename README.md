# FineDust

## Overview

My first project.  
It is simple C++ project that uses Class & Open API service.  
Due to this project, I can unserstand Class, url-encoding, utf-encoding and Open API.

Class와 Open Api 서비스를 활용한 저의 첫번째 프로젝트 입니다.  
C++로 Open Api에서 미세먼지 데이터를 크롤링하고 파싱하는 과정을 통해, Class 와 url-encoding, utf-encoding, Open Api 등에 대해 이해할 수 있었습니다.  
<br/>

## How To

### Servie key

서비스키는 [공공데이터 포털](https://www.data.go.kr/index.do) 회원가입 후 
[[측정소정보]](https://www.data.go.kr/data/15073877/openapi.do), 
[[대기오염정보]](https://www.data.go.kr/data/15073861/openapi.do)에서 무료로 발급받으실 수 있습니다.  
발급 받은 서비스키는 `src/search.cpp` 파일의 다음과 같은 부분에 입력하시면 됩니다.  
```C++
char* servicekey1(void) {
	std::string apiKey1 = "{여기에 서비스키를 입력하세요 [https://www.data.go.kr/data/15073877/openapi.do]}";
	std::string param_apikey1 = "servicekey=" + apiKey1;
    static char ch_apiKey1[256];
    strcpy_s(ch_apiKey1, param_apikey1.c_str());
    return ch_apiKey1;
}


char* servicekey2(void) {
	std::string apiKey2 = "{여기에 서비스키를 입력하세요 [https://www.data.go.kr/data/15073861/openapi.do]}";
	std::string param_apikey2 = "servicekey=" + apiKey2;
    static char ch_apiKey2[256];
    strcpy_s(ch_apiKey2, param_apikey2.c_str());
    return ch_apiKey2;
}
```  

### Setup  

```console
$ git clone https://github.com/rheefine/fineDust.git
```

### Build

이 프로젝트는 `win32` 환경에서 [CMake](https://cmake.org/)와 [VcPkg](https://github.com/microsoft/vcpkg)를 사용하여 다음과 같이 빌드할 수 있습니다.  

```console
$ cmake -B build -S . "-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]\vcpkg\scripts\buildsystems\vcpkg.cmake"
$ cmake --build build --config debug
```  
  
### Run
```console
$ .\build\debug\finedust.exe
```
<br/>

## References

* [libcurl examples](https://curl.se/libcurl/c/example.html)  
  * https://stackoverflow.com/questions/50013204/jsoncpp-to-parse-from-url
  * https://stackoverflow.com/questions/19582838/add-paramethers-to-libcurl-get-in-c/19582883#19582883
* [cp949 <-> UTF-8 / using libiconv](https://webnautes.tistory.com/1466)
* [URL-encode](http://codepad.org/lCypTglt)
* [Unicode to UTF-8](https://stackoverflow.com/questions/2619897/how-can-i-deal-with-this-encoding)
* https://3001ssw.tistory.com/79  
<br/>

***

## Dependencies

This project uses external libraries:

- cURL, inspired by MIT/X license,https://curl.se/docs/copyright.html
- Jsoncpp, MIT license, https://github.com/open-source-parsers/jsoncpp
- libiconv, LGPL, https://www.gnu.org/software/libiconv/


## License

FineDust is released under the unlicense. In short, use for any purpose 
as long as you don't hold me responsible for anything. It would be 
nice if you'd toss me a mail if you play with this thing.

