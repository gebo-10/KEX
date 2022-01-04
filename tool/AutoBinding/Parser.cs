using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClangSharp;
using UnityEngine;
namespace AutoMetaData
{
    public class Parser
    {
        public static void DumpAST(string file)//Application.streamingAssetsPath + "/person.h"
        {
            var index = clang.createIndex(0, 0);
            string[] command_line_args = { "-x", "c++" };
            CXTranslationUnit unit = clang.parseTranslationUnit(index, file, command_line_args, command_line_args.Length, out CXUnsavedFile unsaved_files, 0, 0);
            CXCursor cursor = clang.getTranslationUnitCursor(unit);

            CXClientData clentData = new CXClientData();
            clang.visitChildren(cursor, (CXCursor c, CXCursor parent, IntPtr client_data) =>
            {
                Debug.Log("Name: " + clang.getCursorSpelling(c)
                + " ,Kind: " + clang.getCursorKindSpelling(clang.getCursorKind(c))
                + " ,Type: " + clang.getCursorType(c));
                return CXChildVisitResult.CXChildVisit_Recurse;
            }, clentData);

            clang.disposeTranslationUnit(unit);
            clang.disposeIndex(index);
        }
        public static MetaDatabase ParserFile(string file)//Application.streamingAssetsPath + "/person.h"
        {
            var index = clang.createIndex(0, 0);
            string[] command_line_args = { "-x", "c++" };
            CXTranslationUnit unit = clang.parseTranslationUnit(index, file, command_line_args, command_line_args.Length, out CXUnsavedFile unsaved_files, 0, 0);
            CXCursor cursor = clang.getTranslationUnitCursor(unit);

            MetaDatabase meta_database = new MetaDatabase();
            meta_database.filename = file;

            CXClientData clentData = new CXClientData();
            clang.visitChildren(cursor, (CXCursor c, CXCursor parent, IntPtr client_data) =>
            {
                var kind = clang.getCursorKind(c);
                switch (kind)
                {
                    case CXCursorKind.CXCursor_ClassDecl:
                    case CXCursorKind.CXCursor_StructDecl:
                        {
                            var meta = ParserClass(c, parent, client_data);
                            meta_database.class_list.Add(meta.name, meta);
                            return CXChildVisitResult.CXChildVisit_Continue;
                        }
                        break;
                    case CXCursorKind.CXCursor_EnumDecl:
                        {
                            var meta = ParserEnum(c, parent, client_data);
                            meta_database.enum_list.Add(meta.name, meta);
                            return CXChildVisitResult.CXChildVisit_Continue;
                        }
                        break;
                    case CXCursorKind.CXCursor_FunctionDecl:
                        {
                            MethodField f = new MethodField();
                            f.type = MethodType.Naked;
                            f.name= clang.getCursorSpelling(c).ToString();
                            f.decl = clang.getCursorType(c).ToString();
                            meta_database.function_list.Add(f.name,f);
                            return CXChildVisitResult.CXChildVisit_Continue;
                        }
                        break;
                }
                return CXChildVisitResult.CXChildVisit_Recurse;
            }, clentData);

            clang.disposeTranslationUnit(unit);
            clang.disposeIndex(index);

            return meta_database;
        }
        public static ClassMateData ParserClass(CXCursor c, CXCursor parent, IntPtr client_data)
        {
            ClassMateData class_meta_data = new ClassMateData();
            CXType cxtype = clang.getCursorType(c);
            class_meta_data.name = cxtype.ToString();
            Debug.Log("Class = " + class_meta_data.name);

            CXClientData clentData = new CXClientData();
            clang.visitChildren(c, (CXCursor field_cursor, CXCursor parent, IntPtr client_data) => {
                if (clang.getCursorKind(field_cursor) == CXCursorKind.CXCursor_CXXBaseSpecifier)
                {
                    class_meta_data.parent = clang.getCursorType(field_cursor).ToString();
                    return CXChildVisitResult.CXChildVisit_Recurse;
                }
                else
                {
                    ParserClassField(ref class_meta_data, field_cursor);
                    return CXChildVisitResult.CXChildVisit_Continue;
                }

            }, clentData);
            return class_meta_data;
        }

        public static void ParserClassField(ref ClassMateData class_meta_data, CXCursor field_cursor)
        {
            var field_name = clang.getCursorSpelling(field_cursor).ToString();
            var field_type = clang.getCursorType(field_cursor);
            Debug.Log("Field = " + field_name);
            switch (clang.getCursorKind(field_cursor))
            {
                case CXCursorKind.CXCursor_FieldDecl:
                    {
                        ValueField f = new ValueField();
                        f.name = field_name;
                        f.decl = field_type.ToString();
                        class_meta_data.values.Add(f);
                        break;
                    }
                case CXCursorKind.CXCursor_CXXMethod:
                    {
                        MethodField f = new MethodField();
                        f.name = field_name;
                        f.type = MethodType.Member;
                        f.isstatic = clang.CXXMethod_isStatic(field_cursor) == 1;
                        f.isvirtual = clang.CXXMethod_isVirtual(field_cursor) == 1;
                        f.decl = field_type.ToString();
                        class_meta_data.methods.Add(f);
                        break;
                    }
                case CXCursorKind.CXCursor_Constructor:
                    {
                        MethodField f = new MethodField();
                        f.name = field_name;
                        f.type = MethodType.Constructor;
                        f.isstatic = false;
                        f.isvirtual = false;
                        f.decl = field_type.ToString();
                        class_meta_data.constructor.Add(f);
                        break;
                    }
            }
        }
        public static EnumMateData ParserEnum(CXCursor c, CXCursor parent, IntPtr client_data)
        {
            EnumMateData enum_meta_data = new EnumMateData();
            CXType cxtype = clang.getCursorType(c);
            enum_meta_data.name = cxtype.ToString();
            Debug.Log("Class = " + enum_meta_data.name);

            CXClientData clentData = new CXClientData();
            clang.visitChildren(c, (CXCursor field_cursor, CXCursor parent, IntPtr client_data) => {
                EnumItem enum_item = new EnumItem();
                enum_item.name = clang.getCursorSpelling(field_cursor).ToString();
                enum_item.value = (int)clang.getEnumConstantDeclValue(field_cursor);
                enum_meta_data.fields.Add(enum_item);
                return CXChildVisitResult.CXChildVisit_Continue;
            }, clentData);
            return enum_meta_data;
        }
    }
}
