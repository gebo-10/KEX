using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClangSharp;
namespace AutoMetaData
{
    [Serializable]
    public enum MetaFunction
    {
        construct,
        index,
        new_index,
        mode,
        call,
        call_function = call,
        metatable,
        to_string,
        length,
        unary_minus,
        addition,
        subtraction,
        multiplication,
        division,
        modulus,
        power_of,
        involution = power_of,
        concatenation,
        equal_to,
        less_than,
        less_than_or_equal_to,
        garbage_collect,
        floor_division,
        bitwise_left_shift,
        bitwise_right_shift,
        bitwise_not,
        bitwise_and,
        bitwise_or,
        bitwise_xor,
        pairs,
        ipairs,
        next,
        type,
        type_info,
        call_construct,
        storage,
        gc_names,
        static_index,
        static_new_index,
    };
    [Serializable]
    public class ValueField
    {
        public string name;
        public string decl;
    }
    [Serializable]
    public enum MethodType
    {
        Constructor,
        Member,
        Static,
        Operator,
        Naked,
    }
    [Serializable]
    public class MethodField
    {
        public string name;
        public string decl;
        //public string base_class;
        //public bool isoverload;
        public bool isvirtual;
        public bool isstatic;
        public MethodType type;
        //public ValueField return_type;
        //public List<ValueField> args=new List<ValueField>();
    }
    [Serializable]
    public class ClassMateData
    {
        public string name;
        public string parent;
        public bool is_absolate;
        public List<MethodField> constructor=new List<MethodField>();
        public List<ValueField> values=new List<ValueField>();
        public Dictionary<string, List<MethodField> > methods=new Dictionary<string, List<MethodField> >();
        //public List<MethodField> methods=new List<MethodField>();
    }
    [Serializable]
    public class EnumItem
    {
        public string name;
        public int value;
        public string type;
    }
    [Serializable]
    public class EnumMateData
    {
        public string name;
        public List<EnumItem> fields=new List<EnumItem>();
    }
    [Serializable]
    public class MetaDatabase
    {
        public string filename;
        public Dictionary<string, ClassMateData> class_list=new Dictionary<string, ClassMateData>();
        public Dictionary<string, EnumMateData> enum_list=new Dictionary<string, EnumMateData>();
        public Dictionary<string, MethodField> function_list=new Dictionary<string, MethodField>();
    }
}
