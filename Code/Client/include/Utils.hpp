#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

#include <nethost.h>

#include <coreclr_delegates.h>
#include <hostfxr.h>
#include <cassert>

namespace Utils {

	class FileManager {
	public:

		[[nodiscard]] static std::string GetAppPath() {
			char buffer[MAX_PATH];
			GetModuleFileNameA(NULL, buffer, MAX_PATH);
			std::string::size_type pos = std::string(buffer).find_last_of("\\/");

			return std::string(buffer).substr(0, pos);
		}
	};

	class NetCore {
		static hostfxr_initialize_for_runtime_config_fn init_fptr;
		static hostfxr_get_runtime_delegate_fn get_delegate_fptr;
		static hostfxr_close_fn close_fptr;
	public:

		static void* load_library(const char_t* path) {
			HMODULE h = ::LoadLibraryW(path);
			assert(h != nullptr);
			return (void*)h;
		}

		static void* get_export(void* h, const char* name) {
			void* f = ::GetProcAddress((HMODULE)h, name);
			assert(f != nullptr);
			return f;
		}

		static bool load_hostfxr() {
			char_t buffer[MAX_PATH];
			size_t buffer_size = sizeof(buffer) / sizeof(char_t);
			int rc = get_hostfxr_path(buffer, &buffer_size, nullptr);
			if (rc != 0)
				return false;

			// Load hostfxr and get desired exports
			void* lib = load_library(buffer);
			init_fptr = (hostfxr_initialize_for_runtime_config_fn)get_export(lib, "hostfxr_initialize_for_runtime_config");
			get_delegate_fptr = (hostfxr_get_runtime_delegate_fn)get_export(lib, "hostfxr_get_runtime_delegate");
			close_fptr = (hostfxr_close_fn)get_export(lib, "hostfxr_close");

			return (init_fptr && get_delegate_fptr && close_fptr);
		}

		static load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* config_path) {
			// Load .NET Core
			void* load_assembly_and_get_function_pointer = nullptr;
			hostfxr_handle cxt = nullptr;
			int rc = init_fptr(config_path, nullptr, &cxt);
			if (rc != 0 || cxt == nullptr)
			{
				std::cerr << "Init failed: " << std::hex << std::showbase << rc << std::endl;
				close_fptr(cxt);
				return nullptr;
			}

			// Get the load assembly function pointer
			rc = get_delegate_fptr(
				cxt,
				hdt_load_assembly_and_get_function_pointer,
				&load_assembly_and_get_function_pointer);
			if (rc != 0 || load_assembly_and_get_function_pointer == nullptr)
				std::cerr << "Get delegate failed: " << std::hex << std::showbase << rc << std::endl;

			close_fptr(cxt);
			return (load_assembly_and_get_function_pointer_fn)load_assembly_and_get_function_pointer;
		}
	};

}