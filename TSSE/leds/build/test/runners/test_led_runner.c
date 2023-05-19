/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_todos_los_leds_inician_apagados(void);
extern void test_prender_un_led(void);
extern void test_prender_y_apagar_un_led(void);
extern void test_prender_y_apagar_varios_leds(void);
extern void test_prendo_led_y_consulto_estado(void);
extern void test_apago_led_y_consulto_estado(void);
extern void test_prendo_todos_y_verifico_todos_prendidos(void);
extern void test_prendo_todo_apago_uno_verifico_estado(void);
extern void test_prendo_todo_apago_todo_verifico_estado(void);
extern void test_prendido_limite_inferior(void);
extern void test_apagado_limite_inferior(void);
extern void test_prendido_limite_superior(void);
extern void test_apagado_limite_superior(void);
extern void test_revisar_argumentos_erroneos_prender(void);
extern void test_revisar_argumentos_erroneos_apagar(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

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
  UnityBegin("test_led.c");
  run_test(test_todos_los_leds_inician_apagados, "test_todos_los_leds_inician_apagados", 25);
  run_test(test_prender_un_led, "test_prender_un_led", 34);
  run_test(test_prender_y_apagar_un_led, "test_prender_y_apagar_un_led", 40);
  run_test(test_prender_y_apagar_varios_leds, "test_prender_y_apagar_varios_leds", 47);
  run_test(test_prendo_led_y_consulto_estado, "test_prendo_led_y_consulto_estado", 57);
  run_test(test_apago_led_y_consulto_estado, "test_apago_led_y_consulto_estado", 63);
  run_test(test_prendo_todos_y_verifico_todos_prendidos, "test_prendo_todos_y_verifico_todos_prendidos", 69);
  run_test(test_prendo_todo_apago_uno_verifico_estado, "test_prendo_todo_apago_uno_verifico_estado", 76);
  run_test(test_prendo_todo_apago_todo_verifico_estado, "test_prendo_todo_apago_todo_verifico_estado", 83);
  run_test(test_prendido_limite_inferior, "test_prendido_limite_inferior", 91);
  run_test(test_apagado_limite_inferior, "test_apagado_limite_inferior", 96);
  run_test(test_prendido_limite_superior, "test_prendido_limite_superior", 101);
  run_test(test_apagado_limite_superior, "test_apagado_limite_superior", 106);
  run_test(test_revisar_argumentos_erroneos_prender, "test_revisar_argumentos_erroneos_prender", 114);
  run_test(test_revisar_argumentos_erroneos_apagar, "test_revisar_argumentos_erroneos_apagar", 124);

  return UnityEnd();
}
