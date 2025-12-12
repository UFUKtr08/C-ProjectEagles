cmake_minimum_required(VERSION 3.10)

# Proje İsmi
project(MySweetHome)

# C++98 Standardı (Hoca zorunlu tutmuştu)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header dosyalarını tanıt
include_directories(include)

# Kaynak dosyalarını topla
file(GLOB SOURCES "src/*.cpp")

# Çalıştırılabilir dosya oluştur
add_executable(MSH_App ${SOURCES})