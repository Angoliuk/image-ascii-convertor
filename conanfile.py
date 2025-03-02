import os

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy


class MyConanFile(ConanFile):
    name = "dreich"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = "*"

    options = {
        # "fmt/*:header_only": [True, False],
        # "qt/*.shared": [True, False],
        # "qt/*.qtdeclarative": [True, False],
        # "qt/*.qtshadertools": [True, False],
    }

    default_options = {
        "fmt/*:header_only": True,
        # "qt/*.shared": True,
        # "qt/*.qtdeclarative": True,
        # "qt/*.qtshadertools": True,
    }

    def requirements(self):
        self.requires("spdlog/1.13.0")
        self.requires("stb/cci.20220909")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package_info(self):
        self.cpp_info.libs = ["Dreich"]

    def deploy(self):
        copy(self, "*", src=self.package_folder, dst=self.deploy_folder)
