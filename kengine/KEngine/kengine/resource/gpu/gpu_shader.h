#pragma once
#include "gpu_resource.h"
#include "gpu_buffer.h"
namespace kengine {
	class GPUShader
	{
	public:
		GPUID program_id;
		GPUShader(string_view vs_source, string_view fs_source)
		{
			auto vs = build_shader(GL_VERTEX_SHADER, vs_source);
			auto fs = build_shader(GL_FRAGMENT_SHADER, fs_source);
			auto succ = build_program(vs, fs, 0, 0, 0);
			glDeleteShader(vs);
			glDeleteShader(fs);
			//delete_shader(gs);
			//delete_shader(ts_control);
			//delete_shader(ts_evaluation);
		}

		~GPUShader()
		{
			if (program_id != 0)
			{
				glDeleteProgram(program_id);
			}
		}

		void bind() {
			glUseProgram(program_id);
		}

		void unbind() {
			glUseProgram(0);
		}
	private:
		GPUID build_shader(int shader_type, string_view source) {
			if (source.empty())
			{
				return 0;
			}
			GPUID shader = glCreateShader(shader_type);

			if (0 == shader)
			{
				error("Create vertex shader failed :{}", source);
				return 0;
			}

			const GLchar* vCodeArray[1] = { source.data() };
			glShaderSource(shader, 1, vCodeArray, NULL);
			glCompileShader(shader);

			GLint compileResult;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
			if (GL_FALSE == compileResult)
			{
				GLint logLen;

				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0)
				{
					char* log = (char*)malloc(logLen);
					GLsizei written;
					glGetShaderInfoLog(shader, logLen, &written, log);
					if (shader_type == GL_VERTEX_SHADER) {
						error("vertex shader compile log : {}", log);
					}
					else if (shader_type == GL_FRAGMENT_SHADER) {
						error("fragment shader compile log : {}", log);
					}
					
					free(log);
				}
				return 0;
			}
			return shader;
		}
		bool build_program(GPUID fs, GPUID vs, GPUID gs, GPUID ts_control, GPUID ts_evaluation) {
			if (fs == 0 || vs == 0)
			{
				error("build_program error :fs == 0 || vs == 0");
				return false;
			}

			GLuint program = glCreateProgram();
			if (!program)
			{
				error("create program failed");
				return false;
			}

			glAttachShader(program, fs);
			glAttachShader(program, vs);
			if (gs != 0) {
				glAttachShader(program, gs);
			}
			if (ts_control != 0 && ts_evaluation != 0) {
				glAttachShader(program, ts_control);
				glAttachShader(program, ts_evaluation);
			}

			glLinkProgram(program);

			//int block_index = glGetUniformBlockIndex(program, "Global");
			//glUniformBlockBinding(program, block_index, 0);

			//block_index = glGetUniformBlockIndex(program, "Light");
			//glUniformBlockBinding(program, block_index, 1);


			GLint linkStatus;
			glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
			if (GL_FALSE == linkStatus)
			{
				error("ERROR : link shader program failed");
				GLint logLen;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0)
				{
					char* log = (char*)malloc(logLen);
					GLsizei written;
					glGetProgramInfoLog(program, logLen,
						&written, log);
					error("Program log :{}", log);
				}
				glDeleteProgram(program);
				program_id = 0;
				return false;
			}

			program_id = program;
			return true;
		}
	};

	
	typedef shared_ptr<GPUShader> GPUShaderPtr;
}