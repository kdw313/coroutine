# Magic
Auto**magic**ally working C++ Coroutine: [Documentation](https://github.com/luncliff/Magic/wiki)

[![Build status](https://ci.appveyor.com/api/projects/status/9eoy07qfxxqghop3?svg=true)](https://ci.appveyor.com/project/luncliff/magic) [![Build Status](https://travis-ci.org/luncliff/Magic.svg)](https://travis-ci.org/luncliff/Magic)

[![SonarQube: Bugs](https://sonarcloud.io/api/project_badges/measure?project=luncliff-magic&metric=bugs)](https://sonarcloud.io/dashboard?id=luncliff-magic)
[![SonarQube: Code Smells](https://sonarcloud.io/api/project_badges/measure?project=luncliff-magic&metric=code_smells)](https://sonarcloud.io/dashboard?id=luncliff-magic)

## Build
For detailed build steps, reference [`.travis.yml`](/.travis.yml) and [`appveyor.yml`](/appveyor.yml).
 - [Travis CI Docs](https://docs.travis-ci.com/user/languages/cpp/)
 - [AppVeyor Docs](https://www.appveyor.com/docs/)

### Visual Studio 2017(vc141)
  - compiler option: [`/await`](https://blogs.msdn.microsoft.com/vcblog/2015/04/29/more-about-resumable-functions-in-c/) 
  - compiler option: `/std:c++latest`

### Clang 6.0.0 for Windows 
  - Chocolaty [LLVM package](https://chocolatey.org/packages/llvm)
  - Chocolaty [Ninja package](https://chocolatey.org/packages/ninja)
  - Uses CMake for project generation

### Clang 5.0.0 for Linux
Since libc++ apt package doesn't contain experimental headers, the build steps [downloads libc++ and build with them](https://libcxx.llvm.org/docs/BuildingLibcxx.html).

### AppleClang on MacOS
Trigger manual LLVM update before build. Required version is **stable 6.0.0** or later

## Package
Preparing Nuget for Visual Studio users. [The package](https://www.nuget.org/packages/CppMagic/).

## License 
**Feel free for any kind of usage**.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
