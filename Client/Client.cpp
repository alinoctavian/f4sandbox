#include <Windows.h>
#include <iostream>

#include <mono/metadata/assembly.h>
#include <mono/jit/jit.h>
#include <mono/metadata/debug-helpers.h>

void PrintMethod(MonoString* string) {
	char* cppString = mono_string_to_utf8(string);

	std::cout << cppString;

	mono_free(cppString);
}

int main(int argc, wchar_t* argv[])
{
    std::cout << "Test" << std::endl;

    mono_set_dirs("C:\\Program Files\\Mono\\lib",
        "C:\\Program Files\\Mono\\etc");

    MonoDomain* domain = mono_jit_init("CSharp_Domain");

    std::string assemblyPath = "C:\\Users\\again\\source\\f4sandbox\\TestApp\\bin\\Debug\\netcoreapp3.1\\TestApp.dll";

    MonoAssembly* csharpAssembly = mono_domain_assembly_open(domain, assemblyPath.c_str());
   
    if (!csharpAssembly) {
        std::cout << "Assembly failed to open \n";
    }

    MonoImage* image;
    image = mono_assembly_get_image(csharpAssembly);
    if (!image)
    {
        std::cout << "mono_assembly_get_image failed" << std::endl;
    }

	mono_add_internal_call("TestApp.Native::PrintMethod", &PrintMethod);

	//Build a method description object
	MonoMethodDesc* TypeMethodDesc;
	char* TypeMethodDescStr = (char *)"TestApp.Lib:test()";
	TypeMethodDesc = mono_method_desc_new(TypeMethodDescStr, NULL);
	if (!TypeMethodDesc)
	{
		std::cout << "mono_method_desc_new failed" << std::endl;
		system("pause");
		return 1;
	}

	//Search the method in the image
	MonoMethod* method;
	method = mono_method_desc_search_in_image(TypeMethodDesc, image);
	if (!method)
	{
		std::cout << "mono_method_desc_search_in_image failed" << std::endl;
		system("pause");
		return 1;
	}

	//run the method
	std::cout << "Running the static method: " << TypeMethodDescStr << std::endl;
	mono_runtime_invoke(method, nullptr, nullptr, nullptr);

    return 0;
}
