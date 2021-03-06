#ifndef __LANG__
#define __LANG__

#include <string>
#include <unistd.h>
#include <cstdlib>
#include "common.h"
#include "logger.h"

void exec_compile(int compiler) {
	switch (compiler) {
		case COMPILER::C:
			LOG_TRACE("Start compile: gcc -o %s %s -static -w -lm -std=c99 -O2 -DONLINE_JUDGE",
            		FILE_PATH::exec.c_str(), FILE_PATH::source_code.c_str());
            execlp("gcc", "gcc", "-o", FILE_PATH::exec.c_str(), FILE_PATH::source_code.c_str(),
            		"-static", "-w", "-lm", "-std=c99", "-O2", "-DONLINE_JUDGE", NULL);
            break;
		case COMPILER::CPP:
			LOG_TRACE("Start compile: g++ -o %s %s -static -w -lm -O2 -DONLINE_JUDGE",
                    FILE_PATH::exec.c_str(), FILE_PATH::source_code.c_str());
            execlp("g++", "g++", "-o", FILE_PATH::exec.c_str(), FILE_PATH::source_code.c_str(),
                    "-static", "-w", "-lm", "-DONLINE_JUDGE", NULL);
            break;
        case COMPILER::CPP11:
			LOG_TRACE("Start compile: g++ -o %s %s -static -w -lm -O2 -std=c++11 -DONLINE_JUDGE",
                    FILE_PATH::exec.c_str(), FILE_PATH::source_code.c_str());
            execlp("g++", "g++", "-o", FILE_PATH::exec.c_str(), FILE_PATH::source_code.c_str(),
                    "-static", "-w", "-lm", "-std=c++11", "-DONLINE_JUDGE", NULL);
            break;
		case COMPILER::JAVA:
			LOG_TRACE("Start compile: javac %s -d %s", FILE_PATH::source_code.c_str(), 
					FILE_PATH::runtime_dir.c_str());
            execlp("javac", "javac", "-J-Xms32m", "-J-Xmx256m", FILE_PATH::source_code.c_str(),                    "-d", FILE_PATH::runtime_dir.c_str(), NULL);
            break;
		case LANG::PYTHON:
			break;
		default:
			LOG_WARNING("exec compile error");
        	exit(EXIT::COMPILE);
	}
}

void exec_run(int compiler) {
	switch (compiler) {
		case COMPILER::C:
		case COMPILER::CPP:
		case COMPILER::CPP11:
			execl("./a.out", "a.out", NULL);
            break;
		case COMPILER::JAVA:
			execlp("java", "java", "Main", NULL);
            break;
		case COMPILER::PYTHON:
			execlp("python", "python", FILE_PATH::source_code_name.c_str(), NULL);
			break;
		case COMPILER::PYTHON3:
			execlp("python3", "python3", FILE_PATH::source_code_name.c_str(), NULL);
			break;
		default:
			LOG_WARNING("exec run error");
        	exit(EXIT::PRE_JUDGE_PTRACE);
	}
}

void exec_compile_spj(int lang) {
	switch (lang) {
		case LANG::C:
			LOG_TRACE("Start compile spj: gcc %s -o %s",
            		FILE_PATH::spj_code.c_str(), FILE_PATH::exec.c_str());
            execlp("gcc", "gcc", FILE_PATH::spj_code.c_str(), "-o", 
            		FILE_PATH::exec_spj.c_str(), NULL);
            break;
		case LANG::CPP:
			LOG_TRACE("Start compile spj: g++ %s -o %s",
                    FILE_PATH::spj_code.c_str(), FILE_PATH::exec.c_str()); 
			//cout << FILE_PATH::spj_code << endl;
			//cout << FILE_PATH::exec_spj << endl;
            execlp("g++", "g++", FILE_PATH::spj_code.c_str(), "-o", 
            		FILE_PATH::exec_spj.c_str(), NULL);
            break;
		default:
			LOG_WARNING("exec compile spj error");
        	exit(EXIT::COMPILE_SPJ);
	}
}

void exec_spj(int lang) {
	switch (lang) {
		case LANG::C:
		case LANG::CPP:
			execl((FILE_PATH::runtime_dir + "/SPJ").c_str(), "SPJ", NULL);
            break;
		default:
			LOG_WARNING("exec spj error");
        	exit(EXIT::PRE_JUDGE_PTRACE);
	}
}

#endif
