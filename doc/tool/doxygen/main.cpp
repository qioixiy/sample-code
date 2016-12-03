/**
 * @file     main.cpp
 * @brief    This is a brief description.
 * @details  This is the detail description.
 * @author   xxx
 * @date     2016-12-01
 * @version  A001
 * @par Copyright (c):
 *   xxx
 * @par History:
 *   version: author, date, desc\n
 * @attention

 * @code
 * @endcode

 * @bug coredump
 * @todo add feature
 */

/** Description of the macro */
#define M1 0 ///< M1 macro.

#define M2 1 ///< M2 macro.

/**  Description of global variable  */
int g_xxx = 0;

static int s_xxx = 0; ///<  Description of static variable

/**
 * The brief description.
 * The detail description.
 */
typedef struct
{
  int var1;///< Description of the member variable
}s1;

class Class1 {
public:
  Class1() {
    ;
  }
  virtual ~Class1() {
    ;
  }

  void Run() {
    prot();
  }

protected:
  void prot() {
    priv();
  }

private:
  void priv() {
    tests();
  }
};

int test1(int inArgName, int &outArgName);
int test2(int inArgName, int &outArgName);

/**
 * all of the tests
 */
void tests() {
  int out;
  test1(1, out);
  test2(2, out);
}

/**
 * this is main entry
 */
int main()
{
  Class1 c1;
  c1.Run();
}

/**
 * This is a brief description.
 * This is a detail description.
 * @param[in]   inArgName input argument description.
 * @param[out]  outArgName output argument description.
 * @retval OK success
 * @retval ERROR failed
 * @par flag
 *      reverse
 * @par other
 *      none
 * @par history
 *      note
 */
int test1(int inArgName, int &outArgName) {
  outArgName = inArgName;
  return 0;
}


/**
 * This is a brief description.
 * This is a detail description.
 * @param[in]   inArgName input argument description.
 * @param[out]  outArgName output argument description.
 * @retval OK success
 * @retval ERROR failed
 * @par flag
 *      reverse
 * @par other
 *      none
 * @par history
 *      note
 */
int test2(int inArgName, int &outArgName) {
  outArgName = inArgName;
  return 0;
}
