#pragma once
#include <string>
#include <map>

enum DataType {
	Void,
	Bool,
	Byte,
	Ubyte,
	Short,
	Ushort,
	Int32,
	Uint32,
	Int64,
	Uint64,
	Float,
	Double,
	String,
	PrimitiveType,

	Context,
};

struct StructField //��Ա  ��������ֵ�Ͳ���  ָ��ָ������
{
	DataType type;
	bool is_pointer;
	bool is_function;
	int array_count; //Ĭ��1��
	int offset;
	int len;
};

union TypeField {
	StructField member;
	int enum_index;
};
enum TypeKind {
	Struct,
	Enum,
};
class Type
{
public:
	DataType type;
	TypeKind kind;
	std::string name;
	int size;
	std::map<std::string, TypeField> fields;
};
//struct FunctionType {
//	Type returnType;
//	Type args[];
//};
std::map<DataType, Type> types;

struct Test {
	int a;
	int* b;
	int** c;//��֧��
	int d[5];
	int* e[5];//֧��
};