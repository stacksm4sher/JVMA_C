#ifndef JVMA_JVM_STRUCTS_H
#define JVMA_JVM_STRUCTS_H

typedef unsigned long long u8;
typedef unsigned int u4;
typedef unsigned short u2;
typedef unsigned char u1;

typedef struct {
    u1 tag;
    u2 name_index;
} CONSTANT_Class_info;

typedef struct {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct {
    u1 tag;
    u2 string_index;
} CONSTANT_String_info;

typedef struct {
    u1 tag;
    u4 bytes;
} CONSTANT_Integer_info;

typedef struct {
    u1 tag;
    u4 bytes;
} CONSTANT_Float_info;

typedef struct {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
} CONSTANT_Long_info;

typedef struct {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
} CONSTANT_Double_info;

typedef struct {
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct {
    u1 tag;
    u2 length;
    u1 *bytes; // [length]
} CONSTANT_Utf8_info;

typedef struct {
    u1 tag;
    u1 reference_kind;
    u2 reference_index;
} CONSTANT_MethodHandle_info;

typedef struct {
    u1 tag;
    u2 descriptor_index;
} CONSTANT_MethodType_info;

typedef struct {
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
} CONSTANT_Dynamic_info;

typedef struct {
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
} CONSTANT_InvokeDynamic_info;

typedef struct {
    u1 tag;
    u2 name_index;
} CONSTANT_Module_info;

typedef struct {
    u1 tag;
    u2 name_index;
} CONSTANT_Package_info;

typedef struct {
    u1 tag;
    u1 *info;
} cp_info;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info; // [attribute_length]
} attribute_info;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constantvalue_index;
} ConstantValue_attribute;

typedef struct {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} exception_table;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code; // [code_length]
    u2 exception_table_length;
    exception_table *e_table; // [exception_table_length]
    u2 attributes_count;
    attribute_info *attributes; // [attributes_count]
} Code_attribute;

typedef struct {
    u1 tag; /* 0 */
} Top_variable_info;

typedef struct {
    u1 tag; /* 1 */
} Integer_variable_info;

typedef struct {
    u1 tag; /* 2 */
} Float_variable_info;

typedef struct {
    u1 tag; /* 5 */
} Null_variable_info;

typedef struct {
    u1 tag; /* 6 */
} UninitializedThis_variable_info;

typedef struct {
    u1 tag; /* 7 */
    u2 cpool_index;
} Object_variable_info;

typedef struct {
    u1 tag; /* 8 */
    u2 offset;
} Uninitialized_variable_info;

typedef struct {
    u1 tag; /* 4 */
} Long_variable_info;

typedef struct {
    u1 tag; /* 3 */
} Double_variable_info;


union verification_type_info {
    Top_variable_info tvi;
    Integer_variable_info ivi;
    Float_variable_info fvi;
    Long_variable_info lvi;
    Double_variable_info dvi;
    Null_variable_info nvi;
    UninitializedThis_variable_info utvi;
    Object_variable_info ovi;
    Uninitialized_variable_info uvi;
};

typedef struct {
    u1 frame_type; /* 0-63 */
} same_frame;

typedef struct {
    u1 frame_type; /* 64-127 */
    union verification_type_info *stack; // [1]
} same_locals_1_stack_item_frame;

typedef struct {
    u1 frame_type; /* 247 */
    u2 offset_delta;
    union verification_type_info *stack; // [1]
} same_locals_1_stack_item_frame_extended;

typedef struct {
    u1 frame_type; /* 248-250 */
    u2 offset_delta;
} chop_frame;

typedef struct {
    u1 frame_type; /* 251 */
    u2 offset_delta;
} same_frame_extended;

typedef struct {
    u1 frame_type; /* 252-254 */
    u2 offset_delta;
    union verification_type_info *locals; // [frame_type - 251]
} append_frame;

typedef struct {
    u1 frame_type; /* 255 */
    u2 offset_delta;
    u2 number_of_locals;
    union verification_type_info *locals; // [number_of_locals]
    u2 number_of_stack_items;
    union verification_type_info *stack; // [number_of_stack_items]
} full_frame;

union stack_map_frame {
    same_frame sf;
    same_locals_1_stack_item_frame sl1sif;
    same_locals_1_stack_item_frame_extended sl1sife;
    chop_frame cf;
    same_frame_extended sfe;
    append_frame af;
    full_frame ff;
};

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_entries;
    union stack_map_frame *entries; // [number_of_entries]
} StackMapTable_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 *exception_index_table; // [number_of_exceptions]
} Exceptions_attribute;

typedef struct {
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
} Classes;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
} InnerClasses_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 class_index;
    u2 method_index;
} EnclosingMethod_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
} Synthetic_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 signature_index;
} Signature_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 sourcefile_index;
} SourceFile_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 debug_extension; // [attribute_length]
} SourceDebugExtension_attribute;

typedef struct {
    u2 start_pc;
    u2 line_number;
} Line_number_table;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    Line_number_table *line_number_table; // [line_number_table_length]
} LineNumberTable_attribute;

typedef struct {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
} Local_variable_table;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_table_length;
    Local_variable_table *local_variable_table; // [local_variable_table_length]
} LocalVariableTable_attribute;

typedef struct {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 signature_index;
    u2 index;
} Local_variable_type_table;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_type_table_length;
    Local_variable_type_table *local_variable_type_table; // [local_variable_type_table_length]
} LocalVariableTypeTable_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
} Deprecated_attribute;

struct Enum_const_value {
    u2 type_name_index;
    u2 const_name_index;
};

struct Array_value {
    u2 num_values;
    struct element_value *values; // [num_values]
};

union Value {
    u2 const_value_index;
    struct Enum_const_value enum_const_value;
    u2 class_info_index;
    struct annotation *annotation_value; // 1
    struct Array_value array_value;
};

struct element_value {
    u1 tag;
    union Value value;
};

struct Element_value_pairs {
    u2 element_name_index;
    struct element_value value;
};

struct annotation {
    u2 type_index;
    u2 num_element_value_pairs;
    struct Element_value_pairs element_value_pairs;
};

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 num_annotations;
    struct annotation *annotations; // [num_annotations]
} RuntimeVisibleAnnotations_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 num_annotations;
    struct annotation *annotations; // [num_annotations]
} RuntimeInvisibleAnnotations_attribute;

typedef struct {
    u2 num_annotations;
    struct annotation *annotations; // [num_annotations]
} Parameter_annotations;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 num_parameters;
    Parameter_annotations *parameter_annotations; // [num_parameters]
} RuntimeVisibleParameterAnnotations_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 num_parameters;
    Parameter_annotations *parameter_annotations; // [num_parameters]
} RuntimeInvisibleParameterAnnotations_attribute;

typedef struct {
    u1 type_parameter_index;
} Type_parameter_target;

typedef struct {
    u2 supertype_index;
} Supertype_target;

typedef struct {
    u1 type_parameter_index;
    u1 bound_index;
} Type_parameter_bound_target;

typedef struct {
} Empty_target;

typedef struct {
    u1 formal_parameter_index;
} Formal_parameter_target;

typedef struct {
    u2 throws_type_index;
} Throws_target;

typedef struct {
    u2 start_pc;
    u2 length;
    u2 index;
} Table;

typedef struct {
    u2 table_length;
    Table *table; // [table_length]
} Localvar_target;

typedef struct {
    u2 exception_table_index;
} Catch_target;

typedef struct {
    u2 offset;
} Offset_target;

typedef struct {
    u2 offset;
    u1 type_argument_index;
} Type_argument_target;

union Target_info {
    Type_parameter_target type_parameter_target;
    Supertype_target supertype_target;
    Type_parameter_bound_target type_parameter_bound_target;
    Empty_target empty_target;
    Formal_parameter_target formal_parameter_target;
    Throws_target throws_target;
    Localvar_target localvar_target;
    Catch_target catch_target;
    Offset_target offset_target;
    Type_argument_target type_argument_target;
};

typedef struct {
    u1 type_path_kind;
    u1 type_argument_index;
} Path;

typedef struct {
    u1 path_length;
    Path *path; // [path_length]
} type_path;

typedef struct {
    u1 target_type;
    union Target_info target_info;
    type_path target_path;
    u2 type_index;
    u2 num_element_value_pairs;
    struct Element_value_pairs *element_value_pairs; // [num_element_value_pairs]
} type_annotation;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 num_annotations;
    type_annotation *annotations; // [num_annotations]
} RuntimeVisibleTypeAnnotations_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 num_annotations;
    type_annotation *annotations; // [num_annotations]
} RuntimeInvisibleTypeAnnotations_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    struct element_value default_value;
} AnnotationDefault_attribute;

typedef struct {
    u2 bootstrap_method_ref;
    u2 num_bootstrap_arguments;
    u2 *bootstrap_arguments; // [num_bootstrap_arguments]
} Bootstrap_methods;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 num_bootstrap_methods;
    Bootstrap_methods *bootstrap_methods; // [num_bootstrap_methods]
} BootstrapMethods_attribute;

typedef struct {
    u2 name_index;
    u2 access_flags;
} Parameters;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 parameters_count;
    Parameters *parameters; // [parameters_count]
} MethodParameters_attribute;

typedef struct {
    u2 requires_index;
    u2 requires_flags;
    u2 requires_version_index;
} Requires;

typedef struct {
    u2 exports_index;
    u2 exports_flags;
    u2 exports_to_count;
    u2 *exports_to_index; // [exports_to_count]
} Exports;

typedef struct {
    u2 opens_index;
    u2 opens_flags;
    u2 opens_to_count;
    u2 *opens_to_index; // [opens_to_count]
} Opens;

typedef struct {
    u2 provides_index;
    u2 provides_with_count;
    u2 *provides_with_index; // [provides_with_count]
} Provides;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 module_name_index;
    u2 module_flags;
    u2 module_version_index;
    u2 requires_count;
    Requires *requires; // [requires_count]
    u2 exports_count;
    Exports *exports; // [exports_count]
    u2 opens_count;
    Opens *opens; // [opens_count]
    u2 uses_count;
    u2 *uses_index; // [uses_count]
    u2 provides_count;
    Provides *provides; // [provides_count]
} Module_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 package_count;
    u2 *package_index; // [package_count]
} ModulePackages_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 main_class_index;
} ModuleMainClass_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 host_class_index;
} NestHost_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    u2 *classes; // [number_of_classes]
} NestMembers_attribute;

typedef struct {
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes; // [attributes_count]
} record_component_info;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 components_count;
    record_component_info *components; // [components_count]
} Record_attribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    u2 *classes; // [number_of_classes]
} PermittedSubclasses_attribute;

typedef
struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    Classes *classes; // [number_of_classes]
    attribute_info *attributes; // [attributes_count]
} field_info;

typedef struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes; // [attributes_count]
} method_info;

typedef struct {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool; // [constant_pool_count-1]
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces; // [interfaces_count]
    u2 fields_count;
    field_info fields; // [fields_count]
    u2 methods_count;
    method_info methods; // [methods_count]
    u2 attributes_count;
    attribute_info attributes; // [attributes_count]
} ClassFile;

#endif //JVMA_JVM_STRUCTS_H
