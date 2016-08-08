#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

#include "skinning_glsl.cpp"
#include "kedama_glsl.cpp"

namespace Kedama
{
    using std::stringstream;
    using std::string;
    using std::vector;
    using std::runtime_error;

    enum class GLSLPreprocessTokenType
    {
        IDENTIFIER,QUO,STRING
    };

    struct GLSLPreprocessToken
    {
        GLSLPreprocessTokenType type;
        string identifier_name;
        string content;
        unsigned int row;
    };


    class GLSLPreprocessor
    {
    public:
        void Parse(const string& src,const string& filename="")
        {
            m_is.str(src);
            string* current_shader=nullptr;
            string next_filename;
            GLSLPreprocessToken token = GetNextToken();
            while(!m_is.eof())
            {
                if(token.type==GLSLPreprocessTokenType::IDENTIFIER)
                {
                    if(token.identifier_name=="vertex_shader_begin")
                    {
                        if(current_shader!=nullptr)
                        {
                            stringstream ts;
                            ts<<token.row;
                            throw runtime_error(filename+"("+ts.str()+"):unexpected identifier '"+token.identifier_name+"'");
                        }
                        current_shader=&m_vertex_shader;
                        token=GetNextToken();
                    }
                    else if(token.identifier_name=="fragment_shader_begin")
                    {
                        if(current_shader!=nullptr)
                        {
                            stringstream ts;
                            ts<<token.row;
                            throw runtime_error(filename+"("+ts.str()+"):unexpected identifier '"+token.identifier_name+"'");
                        }
                        current_shader=&m_fragment_shader;
                        token=GetNextToken();
                    }
                    else if(token.identifier_name=="vertex_shader_end"||token.identifier_name=="fragment_shader_end")
                    {
                        current_shader=nullptr;
                        token=GetNextToken();
                    }
                    /*else if(token.identifier_name=="include")
                    {
                        token=GetNextToken();
                        if(token.type==GLSLPreprocessTokenType::QUO)
                        {
                            token=GetNextToken();
                            GLSLPreprocessToken next_token=GetNextToken();
                            if(token.type==GLSLPreprocessTokenType::STRING&&next_token.type!=GLSLPreprocessTokenType::QUO)
                            {
                                stringstream ts;
                                ts<<token.row;
                                throw runtime_error(filename+"("+ts.str()+ "):unexpected symbol");
                            }
                            GLSLPreprocessor sub_preprocessor;
                            sub_preprocessor.m_include_paths=m_include_paths;
                            string prase_src;
                            if(token.content=="kedama.glsl"||token.content=="skinning.glsl")
                            {
                                if(token.content=="kedama.glsl")
                                {
                                    prase_src=_kedama_glsl;
                                    next_filename="kedama.glsl";
                                }
                                else if(token.content=="skinning.glsl")
                                {
                                    prase_src=_skinning_glsl;
                                    next_filename="skinning.glsl";
                                }
                            }
                            else//FileSystem 类未写
                            {
                                stringstream ts;
                                ts<<token.row;
                                throw runtime_error(filename+"("+ts.str()+ "):No such found file");
                                    //FileSystem& fs=FileSystem::GetSingleton();
                            }

                            try
                            {
                                sub_preprocessor.Parse(prase_src,next_filename);
                            }
                            catch(runtime_error e)
                            {
                                throw e;
                            }

                            m_vertex_shader+=sub_preprocessor.GetVertexShader();
                            m_fragment_shader+=sub_preprocessor.GetFragmentShader();
                            token=GetNextToken();
                        }
                    }*/
                    else
                    {
                        if(current_shader==nullptr)
                        {
                            stringstream ts;
                            ts<<token.row;
                            throw runtime_error(filename+"("+ts.str()+ "):unexpected symbol");
                        }
                        (*current_shader)+="#"+token.identifier_name+" ";
                        token=GetNextToken();
                        while(token.type==GLSLPreprocessTokenType::STRING)
                        {
                            (*current_shader)+=token.content+" ";
                            token=GetNextToken();
                        }
                    }
                }
                else if(token.type==GLSLPreprocessTokenType::STRING)
                {
                    (*current_shader)+=token.content;
                    token=GetNextToken();
                }
                else
                {
                    stringstream ts;
                    ts<<token.row;
                    throw runtime_error(filename+"("+ts.str()+ "):unexpected symbol");
                    token=GetNextToken();
                }
            }
        }

        void AddIncludePath(const string& path)
        {
            m_include_paths.push_back(path);
        }

        string GetVertexShader()
        {
            return m_vertex_shader;
        }

        string GetFragmentShader()
        {
            return m_fragment_shader;
        }

    private:

        GLSLPreprocessToken GetNextToken()
        {
            GLSLPreprocessToken token;
            int ch=0;
            do
            {
                ch=m_is.get();
                if(ch=='\n')++m_current_col;
            }
            while(!m_is.eof()&&(ch=='\n'||ch==' '||ch=='\t'||ch=='\r'));

            if(ch=='#')
            {
                token.type=GLSLPreprocessTokenType::IDENTIFIER;
                do
                {
                    ch=m_is.get();
                    token.identifier_name.push_back(ch);
                }while(!m_is.eof()&&ch!='\n'&&ch!=' '&&ch!='"');
                if(!m_is.eof())
                    m_is.seekg(-1,std::ios_base::cur);
                token.identifier_name.pop_back();
            }else if(ch=='"')
            {
                token.type=GLSLPreprocessTokenType::QUO;

            }
            else if(!m_is.eof()&&ch>=33&ch<=126)
            {
                m_is.seekg(-1,std::ios_base::cur);
                token.type=GLSLPreprocessTokenType::STRING;
                while(!m_is.eof()&&ch!='"'&&ch!='#')
                {
                    ch=m_is.get();
                    token.content.push_back(ch);
                }
                if(!m_is.eof())
                    m_is.seekg(-1,std::ios_base::cur);
                token.content.pop_back();
            }
            token.row=m_current_col;
            return token;
        }

    private:
        unsigned int m_current_col=1;

        stringstream m_is;//input stream
        string m_vertex_shader;
        string m_fragment_shader;

        vector<string> m_include_paths;
    };
}
