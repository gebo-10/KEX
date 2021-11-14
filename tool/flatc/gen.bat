cd  %~dp0

flatc.exe -o out\cpp\kserialize --cpp --cpp-std c++17 --cpp-ptr-type std::shared_ptr --gen-object-api --reflect-types --reflect-names kengine\asset\common.fbs
flatc.exe -o out\cpp\kserialize --cpp --cpp-std c++17 --cpp-ptr-type std::shared_ptr --gen-object-api --reflect-types --reflect-names kengine\asset\assetbundle.fbs
flatc.exe -o out\cpp\kserialize --cpp --cpp-std c++17 --cpp-ptr-type std::shared_ptr --gen-object-api --reflect-types --reflect-names kengine\asset\shader.fbs 
flatc.exe -o out\cpp\kserialize --cpp --cpp-std c++17 --cpp-ptr-type std::shared_ptr --gen-object-api --reflect-types --reflect-names kengine\namedatabase\namedatabase.fbs

flatc.exe -o out\csharp\kserialize --csharp --gen-object-api --reflect-types --reflect-names kengine\asset\common.fbs
flatc.exe -o out\csharp\kserialize --csharp --gen-object-api --reflect-types --reflect-names kengine\asset\assetbundle.fbs
flatc.exe -o out\csharp\kserialize --csharp --gen-object-api --reflect-types --reflect-names kengine\asset\shader.fbs
flatc.exe -o out\csharp\kserialize --csharp --gen-object-api --reflect-types --reflect-names kengine\namedatabase\namedatabase.fbs