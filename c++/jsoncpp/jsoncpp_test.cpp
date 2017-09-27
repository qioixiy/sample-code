#include <iostream>
#include <jsoncpp/json/json.h>

using namespace std;

string getSkip(int l)
{
    string ret;
    while(--l >= 0) {
        ret += ' ';
    }
    return ret;
}

static int level = 0;

static void printValue(Json::Value v);
static void printObject(Json::Value v) {

    if (v.type() != Json::objectValue) {
        return;
    }
    cout << getSkip(level) << '{' << endl;
    level++;

    Json::Value::Members mem = v.getMemberNames();
    for (auto iter = mem.begin(); iter != mem.end(); iter++) {
        cout<< getSkip(level) << *iter<<":";
        if (v[*iter].type() == Json::objectValue) {
            printObject(v[*iter]);
        } else {
            printValue(v[*iter]);
        }
    }
    level--;
    cout << getSkip(level) << "}," << endl;
}

static void printValue(Json::Value v) {

    if (v.type() == Json::arrayValue) {
        cout<< '[' << endl;
        level++;
        for (auto i = 0u; i < v.size(); i++) {
            if (v[i].type() == Json::objectValue) {
                printObject(v[i]);
            } else {
                printValue(v[i]);
            }
        }
        level--;
        cout<< getSkip(level) << "]," << endl;
    } else if(v.type() == Json::booleanValue) {
        cout<< v.asBool()<<endl;
    }else if (v.type() == Json::stringValue) {
        cout<< v.asString()<<endl;
    } else if (v.type() == Json::realValue) {
        cout<< v.asDouble()<<endl;
    } else if (v.type() == Json::uintValue) {
        cout<< v.asUInt()<<endl;
    } else if (v.type() == Json::intValue){
        cout<< v.asInt()<<endl;
    }
}

static void print(Json::Value v)
{
    if (v.type() == Json::objectValue) {
        printObject(v);
    } else {
        printValue(v);
    }
}

int main()
{
    std::string stream = R"(
{
  "key": "value"
}
)";

    Json::Reader reader;
    Json::Value root;
    if (reader.parse(stream, root)) {
        print(root);
    }
    return 0;
}
