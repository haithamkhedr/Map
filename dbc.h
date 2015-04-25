/* That's the design by contract implemntation file */

#pragma once
#include <string>
#include <stdexcept>
#include <ostream>
#include <sstream>
#include <crtdbg.h>

#if defined(_DEBUG)

	#define REQUIRE0(assertion) \
	if (!(assertion)) throw Require(__FILE__, __LINE__)
	#define REQUIRE(assertion, what) \
	if (!(assertion)) throw Require(__FILE__, __LINE__, what)
	
	#define ENSURE0(assertion) \
	if (!(assertion)) throw Ensure(__FILE__, __LINE__)
	#define ENSURE(assertion, what) \
	if (!(assertion)) throw Ensure(__FILE__, __LINE__, what)
	
	#define INVARIANT0(assertion) \
    if (!(assertion)) throw Invariant(__FILE__, __LINE__)
    #define INVARIANT(assertion, what) \
    if (!(assertion)) throw Invariant(__FILE__, __LINE__, what)
	
#else // Not DESIGN_BY_CONTRACT - disable everything
	#define REQUIRE0(assertion)				((void)0)
	#define REQUIRE(assertion, what)        ((void)0)
	
	#define ENSURE0(assertion)				((void)0)
	#define ENSURE(assertion, what)         ((void)0)
	
	#define INVARIANT0(assertion)			((void)0)
    #define INVARIANT(assertion, what)		((void)0)

#endif // DESIGN_BY_CONTRACT

class DesignByContractException : public std::logic_error
    {
protected:
	// Construction - only for derived classes
    DesignByContractException(const std::string& file, int line, const std::string& what = std::string())
        : std::logic_error(what),  file_(file), line_(line),  errorPrefix_("DesignByContract failed") {}
    
public:
	// Queries
    
	// Exception error prefix
    std::string errorPrefix() const { return errorPrefix_; }
	// Source file
    std::string file() const { return file_; }
    // Line number
	int line() const { return line_; }

    // Source, location and description of exception
    operator std::string() const
    {
		std::ostringstream stream;
        stream << "File: " << file() << "\nLine: " << line() << "\n" << errorPrefix() << ". " << what() << "\n";
        return stream.str();
    }
protected:
	// Commands
    void setErrorPrefix(const std::string& errorPrefix)
	{ 
		errorPrefix_ = errorPrefix;
	}

private:
    std::string file_;
	int			line_;  
	std::string errorPrefix_;
};

class PreconditionException : public DesignByContractException
{
public:
	PreconditionException(const std::string& file, int line, const std::string& what = std::string())
        : DesignByContractException(file, line, what)
        {
            setErrorPrefix("Precondition failed");
        }
};

typedef PreconditionException Require;


class PostconditionException : public DesignByContractException
{
public:
	PostconditionException(const std::string& file, int line, const std::string& what = std::string())
        : DesignByContractException(file, line, what)
        {
            setErrorPrefix("Postcondition failed");
        }
};

typedef PostconditionException Ensure;


class InvariantException : public DesignByContractException
{
public:
	InvariantException(const std::string& file, int line, const std::string& what = std::string())
        : DesignByContractException(file, line, what)
        {
            setErrorPrefix("Invariant failed");
        }
};

typedef InvariantException Invariant;


