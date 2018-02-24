from conans import ConanFile, CMake


class FormigaConan(ConanFile):
    name = "Formiga"
    version = "0.1"
    url = "https://github.com/luisnuxx/formiga"
    license = "MIT; see https://github.com/luisnuxx/formiga/blob/master/LICENSE"
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"

    requires = (("Boost/1.66.0@conan/stable"),
                ("OpenSSL/1.0.2m@conan/stable"))

    # No exports necessary

    def source(self):
        # this will create a hello subfolder, take it into account
        self.run("git clone https://github.com/luisnuxx/formiga.git")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()

        #self.run('cmake %s/formiga %s' % (self.conanfile_directory, cmake.command_line))
        #self.run("cmake --build . %s" % cmake.build_config)
        #self.run("make")

    def package(self):
        self.copy("*.h", dst="include", src="formiga")
        self.copy("*hello.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["Formiga"]