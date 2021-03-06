#pragma once

#include <map>
#include <list>
#include "Instruction.h"
#include "symbols.h"
#include "Lexer.h"
#include "function.h"
#include "variable.h"
#include "token.h"
#include "exception.h"

namespace cflat
{
	class Parser
	{
	public:
		Parser(Lexer* lexer);
		~Parser(void);

		void registerExternalFunction(char* name, ExternalFunctionPtr f);
		int setEntryPoint(char* functionName);

		void parse();
		Exception* parsenext();
		char* getErrorString() { return errorString; }
		bool isError() { return error; }
		int getGlobalStackSize() { return globalStackSize; }

		Variable*					getVariable(char * name);
		Function*					getFunction(char * name);

		std::vector<Instruction>	instructions;
	private:
		DataType					boolexpr(int stackSlot);
		DataType					joinexpr(int stackSlot);
		DataType					bitorexpr(int stackSlot);
		DataType					bitxorexpr(int stackSlot);
		DataType					bitandexpr(int stackSlot);
		DataType					equalityexpr(int stackSlot);
		DataType					relexpr(int stackSlot);
		DataType 					shiftexpr(int stackSlot);
		DataType					mathexpr(int stackSlot);
		DataType					mathterm(int stackSlot);
		DataType					mathunary(int stackSlot);
		DataType					factor(int stackSlot);
		DataType					generalizedTypecast(DataType t, DataType s, int tSlot, int sSlot);
		void						forcedTypecast(DataType t, DataType s, int tSlot);
		void						stmts();
		DataType					decl(bool allowFuncs);
		DataType					datatype();
		void						decls(bool allowFuncs);
		int							functionCall(char* name);
		void						removeAllNonGlobals();

		Lexer*						lexer;
		char						errorString[128];
		bool						error;
		std::vector<Function>		functions;
		std::vector<Variable>		variables;
		int							globalStackSize;
		int							localStackSize;
		int							maxLocalStackSize;
		int							placeholderStack;
		Function*					entryPoint;
	};

}