
list(APPEND CMAKE_MESSAGE_CONTEXT "attempts")

# 仅用于演示通过/失败行为的函数
function(checkSomething resultVar)
    set(${resultVar} YES PARENT_SCOPE)
endfunction()

function(checkSomethingElse resultVar)
    set(${resultVar} NO PARENT_SCOPE)
endfunction()

# 外部检查在此开始
message(CHECK_START "Checking things")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

# 内部检查 1
message(CHECK_START "Checking support for something")
checkSomething(successVar1)
if(successVar1)
    message(CHECK_PASS "supported")
else()
    message(CHECK_FAIL "not supported")
endif()

# 内部检查 2
message(CHECK_START "Checking support for something else")
checkSomethingElse(successVar2)
if(successVar2)
    message(CHECK_PASS "supported")
else()
    message(CHECK_FAIL "not supported")
endif()

# 外部检查在此结束
list(POP_BACK CMAKE_MESSAGE_INDENT)
if(successVar1 OR successVar2)
    message(CHECK_PASS "ok")
else()
    message(CHECK_FAIL "failed")
endif()