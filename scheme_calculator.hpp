#ifndef _SCHEME_CALCULATOR_HPP_
#define _SCHEME_CALCULATOR_HPP_ 1


namespace scheme {

    class SchemeValue;

    struct SchemeValue* car(struct SchemeValue*);

    struct SchemeValue* cdr(struct SchemeValue*);

    struct SchemeValue* read(const std::string&);

    void free_single_obj(struct SchemeValue*);

    void free_obj(struct SchemeValue*);

    int get_new_count();

    int get_free_count();

    namespace calculator {

        struct SchemeValue* eval(struct SchemeValue*);

        int get_eval_value(struct SchemeValue*);

    }

}


#endif
