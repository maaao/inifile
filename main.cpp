#include "readIniFile.hpp"

int main(){
    atlnativeapi::Setting setting;
    std::cout << "mode : " << setting.getAnalyseMode() << std::endl;
    std::cout << "bunkiri : " << setting.getBunkiriLength() << std::endl;
    std::cout << "analyse : " << setting.getAnalyseLength() << std::endl;
}