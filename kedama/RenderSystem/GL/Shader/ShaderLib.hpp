#include <string>

const std::string FsShaderLibraryStr=
R"(#version 450 core
void FS_main();

void main()
{
	FS_main();
}
)";

const std::string VsShaderLibraryStr=
R"(#version 450 core
void VS_main();

void main()
{
	VS_main();
}
)";
