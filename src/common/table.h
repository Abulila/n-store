#ifndef TABLE_H_
#define TABLE_H_

#include "schema.h"
#include "table_index.h"
#include "plist.h"

using namespace std;

class table {
 public:
  table(const std::string& name, schema* _sptr, unsigned int _num_indices)
      : table_name(NULL),
        sptr(_sptr),
        num_indices(_num_indices),
        indices(NULL),
        data(NULL){

    size_t len = name.size();
    char* table_name = new char[len + 1];
    memcpy(table_name, name.c_str(), len + 1);

    pmemalloc_activate(table_name);
  }

  ~table() {
    delete table_name;
    delete sptr;

    if (indices != NULL) {
      // clean up table indices
      vector<table_index*> index_vec = indices->get_data();
      for (table_index* index : index_vec)
        delete index;

      delete indices;
    }
  }

  //private:
  char* table_name;
  schema* sptr;
  unsigned int num_indices;
  plist<table_index*>* indices;

  plist<record*>* data;
};

#endif /* TABLE_H_ */
