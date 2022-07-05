#ifndef LIBEXCEPTIONS_H
#define LIBEXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>
#include <exception>

using namespace std;

namespace MyExceptionErrors {

	class exception {
	public:
		exception() noexcept;
		exception(const exception&) noexcept;
		exception& operator= (const exception&) noexcept;
		virtual ~exception();
		virtual const char* what() const noexcept;
	};

	class FileStreamError : public std::runtime_error
	{
	public:
		FileStreamError() : runtime_error("Opening error") {}
		FileStreamError(std::string msg) : runtime_error(msg.c_str()) {}

	};


	class FileCreateError : public std::runtime_error {
	public:
		FileCreateError() : runtime_error("File creation error") {}
		FileCreateError(std::string msg) : runtime_error(msg.c_str()) {}
	};


	class BadAlloc : public std::runtime_error {
	public:
		BadAlloc() : runtime_error("Invalid array size") {}
		BadAlloc(std::string msg) :runtime_error(msg.c_str()) {}
	};


	class MyException : public exception {
		virtual const char* what() const throw() {
			return "Error, bad array allocation";
		}
	};


	class WrongArgument : public std::runtime_error {
	public:
		WrongArgument() : runtime_error("Wrong argument!") {}
		WrongArgument(std::string msg) : runtime_error(msg.c_str()) {}
	};
}





#endif








