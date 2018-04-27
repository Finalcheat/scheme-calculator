#include <string>
#include <iostream>


namespace scheme {

    enum SchemeValueType
    {
        INTEGER,
        PROC,
        PAIR,
    };

    class SchemeValue;
    typedef struct SchemeValue* (*proc_fn)(struct SchemeValue*);

    struct SchemeValue* add_proc(struct SchemeValue* arguments);

    struct SchemeValue* sub_proc(struct SchemeValue* arguments);

    struct SchemeValue* mul_proc(struct SchemeValue* arguments);

    struct SchemeValue* div_proc(struct SchemeValue* arguments);

    typedef struct SchemeValue
    {
        enum SchemeValueType type;
        union
        {
            int integer;
            struct
            {
                struct SchemeValue* car;
                struct SchemeValue* cdr;
            } pair;
            proc_fn proc;
        } value;
    } SchemeValue;

    typedef struct SchemeValue* (*proc_fn)(struct SchemeValue*);

    struct SchemeValue* car(struct SchemeValue* obj)
    {
        return obj->value.pair.car;
    }

    struct SchemeValue* cdr(struct SchemeValue* obj)
    {
        return obj->value.pair.cdr;
    }

    struct SchemeValue* read_value(const std::string& exp, size_t& pos);

    static int new_count = 0;

    int get_new_count()
    {
        return new_count;
    }

    struct SchemeValue* make_integer(int value)
    {
        struct SchemeValue* obj = new SchemeValue;
        obj->type = INTEGER;
        obj->value.integer = value;
        ++new_count;
        // std::cout << "make_int: " << value << std::endl;
        return obj;
    }

    struct SchemeValue* copy_proc(struct SchemeValue* exp)
    {
        struct SchemeValue* obj = new SchemeValue;
        obj->type = PROC;
        obj->value.proc = exp->value.proc;
        return obj;
    }

    struct SchemeValue* make_proc(char op)
    {
        struct SchemeValue* obj = new SchemeValue;
        obj->type = PROC;
        switch (op)
        {
        case '+':
            obj->value.proc = add_proc;
            break;
        case '-':
            obj->value.proc = sub_proc;
            break;
        case '*':
            obj->value.proc = mul_proc;
            break;
        case '/':
            obj->value.proc = div_proc;
            break;
        }
        ++new_count;
        // std::cout << "make_proc" << std::endl;
        return obj;
    }

    struct SchemeValue* make_pair(struct SchemeValue* car, struct SchemeValue* cdr)
    {
        struct SchemeValue* obj = new SchemeValue;
        obj->type = PAIR;
        obj->value.pair.car = car;
        obj->value.pair.cdr = cdr;
        // std::cout << "make_pair" << std::endl;
        ++new_count;
        return obj;
    }

    static int free_count = 0;

    int get_free_count()
    {
        return free_count;
    }

    void free_single_obj(struct SchemeValue* exp)
    {
        // std::cout << "free type: " << exp->type;
        // if (exp->type == INTEGER)
        // {
        //     std::cout << " (" << exp->value.integer << ")";
        // }
        // std::cout << std::endl;
        ++free_count;
        delete exp;
    }

    void free_obj(struct SchemeValue* exp)
    {
        if (!exp)
        {
            return;
        }

        if (exp->type == PAIR)
        {
            free_obj(car(exp));
            free_obj(cdr(exp));
        }
        free_single_obj(exp);
    }

    struct SchemeValue* add_proc(struct SchemeValue* arguments)
    {
        int sum = 0;
        struct SchemeValue* tmp = arguments;
        while (arguments)
        {
            sum += (car(arguments))->value.integer;
            arguments = cdr(arguments);
        }

        free_obj(tmp);
        return make_integer(sum);
    }

    struct SchemeValue* sub_proc(struct SchemeValue* arguments)
    {
        struct SchemeValue* tmp = arguments;

        struct SchemeValue* carObj = car(arguments);
        arguments = cdr(arguments);

        int init = carObj->value.integer;
        while (arguments)
        {
            init -= car(arguments)->value.integer;
            arguments = cdr(arguments);
        }

        free_obj(tmp);
        return make_integer(init);
    }

    struct SchemeValue* mul_proc(struct SchemeValue* arguments)
    {
        struct SchemeValue* tmp = arguments;

        struct SchemeValue* carObj = car(arguments);
        arguments = cdr(arguments);

        int init = carObj->value.integer;
        while (arguments)
        {
            init *= car(arguments)->value.integer;
            arguments = cdr(arguments);
        }

        free_obj(tmp);
        return make_integer(init);
    }

    struct SchemeValue* div_proc(struct SchemeValue* arguments)
    {
        struct SchemeValue* tmp = arguments;

        struct SchemeValue* carObj = car(arguments);
        arguments = cdr(arguments);

        int init = carObj->value.integer;
        while (arguments)
        {
            init /= car(arguments)->value.integer;
            arguments = cdr(arguments);
        }

        free_obj(tmp);
        return make_integer(init);
    }

    size_t skip_whitespace(const std::string& exp, size_t pos)
    {
        size_t i = pos;
        for (; i < exp.size(); ++i)
        {
            if (exp[i] != ' ')
            {
                break;
            }
        }
        return i;
    }

    struct SchemeValue* read_cons(const std::string& exp, size_t& pos)
    {
        pos = skip_whitespace(exp, pos);
        if (pos >= exp.size())
        {
            return NULL;
        }

        if (exp[pos] == ')')
        {
            ++pos;
            return NULL;
        }

        struct SchemeValue* carObj = read_value(exp, pos);

        struct SchemeValue* cdrObj = read_cons(exp, pos);

        return make_pair(carObj, cdrObj);
    }

    struct SchemeValue* read_value(const std::string& exp, size_t& pos)
    {
        pos = skip_whitespace(exp, pos);
        if (pos >= exp.size())
        {
            return NULL;
        }
        char c = exp[pos];
        ++pos;
        if (isdigit(c))
        {
            int num = (c - '0');
            while (pos < exp.size() && isdigit(exp[pos]))
            {
                num = (num * 10) + (exp[pos] - '0');
                ++pos;
            }
            return make_integer(num);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            return make_proc(c);
        }
        else if (c == '(')
        {
            return read_cons(exp, pos);
        }
        return NULL;
    }

    struct SchemeValue* read(const std::string& exp)
    {
        new_count = 0;
        free_count = 0;
        size_t pos = 0;
        return read_value(exp, pos);
    }

    namespace calculator {

        struct SchemeValue* eval(struct SchemeValue* exp);

        struct SchemeValue* list_of_arguments(struct SchemeValue* exp)
        {
            if (!exp)
            {
                return NULL;
            }
            struct SchemeValue* carObj = car(exp);
            return make_pair(eval(carObj), list_of_arguments(cdr(exp)));
        }

        struct SchemeValue* eval(struct SchemeValue* exp)
        {
            if (!exp)
            {
                return NULL;
            }

            enum SchemeValueType type = exp->type;
            if (type == INTEGER)
            {
                return make_integer(exp->value.integer);
            }
            else if (type == PROC)
            {
                return copy_proc(exp);
            }
            else if (type == PAIR)
            {
                struct SchemeValue* proc = car(exp);
                struct SchemeValue* arguments = list_of_arguments(cdr(exp));
                return (proc->value.proc)(arguments);
            }
            return NULL;
        }

        int get_eval_value(struct SchemeValue* exp)
        {
            return exp->value.integer;
        }

    }

}
