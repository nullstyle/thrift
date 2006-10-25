#ifndef T_PROGRAM_H
#define T_PROGRAM_H

#include <map>
#include <string>
#include <vector>

// For program_name()
#include "main.h"

#include "t_scope.h"
#include "t_base_type.h"
#include "t_typedef.h"
#include "t_enum.h"
#include "t_struct.h"
#include "t_service.h"
#include "t_list.h"
#include "t_map.h"
#include "t_set.h"

/**
 * Top level class representing an entire thrift program. A program consists
 * fundamentally of the following:
 *
 *   Typedefs
 *   Enumerations
 *   Structs
 *   Exceptions
 *   Services
 *
 * The program module also contains the definitions of the base types.
 *
 * @author Mark Slee <mcslee@facebook.com>
 */
class t_program {
 public:
  t_program(std::string path, std::string name) :
    path_(path), 
    name_(name) {
    scope_ = new t_scope();
  }

  t_program(std::string path) :
    path_(path) {
    name_ = program_name(path);
    scope_ = new t_scope();
  }

  // Path accessor   
  const std::string& get_path() const { return path_; }

  // Name accessor
  const std::string& get_name() const { return name_; }

  // Namespace
  const std::string& get_namespace() const { return namespace_; }

  // Accessors for program elements
  const std::vector<t_typedef*>& get_typedefs()  const { return typedefs_;  }
  const std::vector<t_enum*>&    get_enums()     const { return enums_;     }
  const std::vector<t_struct*>&  get_structs()   const { return structs_;   }
  const std::vector<t_struct*>&  get_xceptions() const { return xceptions_; }
  const std::vector<t_service*>& get_services()  const { return services_;  }

  // Program elements
  void add_typedef  (t_typedef* td) { typedefs_.push_back(td);  }
  void add_enum     (t_enum*    te) { enums_.push_back(te);     }
  void add_struct   (t_struct*  ts) { structs_.push_back(ts);   }
  void add_xception (t_struct*  tx) { xceptions_.push_back(tx); }
  void add_service  (t_service* ts) { services_.push_back(ts);  }

  // Programs to include
  const std::vector<t_program*>& get_includes() const { return includes_; }

  // Scoping and namespacing
  void set_namespace(std::string name) {
    namespace_ = name;
  }

  // Scope accessor
  t_scope* scope() {
    return scope_;
  }

  // Includes

  void add_include(std::string path) {
    includes_.push_back(new t_program(path));
  }

  std::vector<t_program*>& get_includes() {
    return includes_;
  }

  // Language specific namespace / packaging

  void set_cpp_namespace(std::string cpp_namespace) {
    cpp_namespace_ = cpp_namespace;
  }

  const std::string& get_cpp_namespace() const {
    return cpp_namespace_;
  }

  void add_cpp_include(std::string path) {
    cpp_includes_.push_back(path);
  }

  const std::vector<std::string>& get_cpp_includes() {
    return cpp_includes_;
  }

  void set_java_package(std::string java_package) {
    java_package_ = java_package;
  }

  const std::string& get_java_package() const {
    return java_package_;
  }


 private:

  // File path
  std::string path_;

  // Name
  std::string name_;

  // Namespace
  std::string namespace_;

  // Included programs
  std::vector<t_program*> includes_;

  // Identifier lookup scope
  t_scope* scope_;

  // Components to generate code for
  std::vector<t_typedef*> typedefs_;
  std::vector<t_enum*>    enums_;
  std::vector<t_struct*>  structs_;
  std::vector<t_struct*>  xceptions_;
  std::vector<t_service*> services_;

  // C++ namespace
  std::string cpp_namespace_;

  // C++ extra includes
  std::vector<std::string> cpp_includes_;

  // Java package
  std::string java_package_;

};

#endif
