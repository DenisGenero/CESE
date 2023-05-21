/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_port.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_verifica_correcta_conversion_datos(void);
extern void test_verifica_lectura_aceleracion_todos_ejes(void);
extern void test_verifica_lectura_aceleracion_eje_x(void);
extern void test_verifica_lectura_resolucion_actual(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_port_Init();
}
static void CMock_Verify(void)
{
  mock_port_Verify();
}
static void CMock_Destroy(void)
{
  mock_port_Destroy();
}

/*=======Setup (stub)=====*/
void setUp(void) {}

/*=======Teardown (stub)=====*/
void tearDown(void) {}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_MPU9255.c");
  run_test(test_verifica_correcta_conversion_datos, "test_verifica_correcta_conversion_datos", 18);
  run_test(test_verifica_lectura_aceleracion_todos_ejes, "test_verifica_lectura_aceleracion_todos_ejes", 27);
  run_test(test_verifica_lectura_aceleracion_eje_x, "test_verifica_lectura_aceleracion_eje_x", 39);
  run_test(test_verifica_lectura_resolucion_actual, "test_verifica_lectura_resolucion_actual", 51);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}
