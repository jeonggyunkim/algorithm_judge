# algorithm_judge

## 사용 방법

linux API를 사용하여 linux에서만 사용 가능합니다

현재 cpp와 python만 사용가능하며, python은 pypy를 이용해 채점합니다

1. input 폴더에 입력파일을, output 폴더에 출력파일을 넣습니다

파일명은 보통 aaa.in, aaa.out과 같은 경우가 많아 해당 형식 기준으로 작성되었습니다.

형식이 조금 다를 경우, judge.py 파일의

```py
pair = {}

for i in input_files:
    for j in output_files:
        if i[:i.find('.')] == j[:j.find('.')]:
            pair[i] = j
```
부분을 알맞게 수정하시면 됩니다.


2. source 폴더에 채점하고자 하는 소스코드들을 넣습니다

파일명은 모두 달라야 합니다. 확장자만 다른 경우도 불가능합니다. 예를 들어 student0.cpp, student0.py 파일이 함께 있으면 안됩니다

3. python3 judge.py를 입력합니다.

채점이 진행되며, 제한 간을 초과하거나 제한 메모리를 초과한 경우 자동으로 프로그램을 종료시킵니다.

제한 시간은 judge.py 파일의 초기 부분에 있는
pair = {}

```py
# Parameter: Time (ms)
time_limit_cpp = 1000
time_limit_python = 3000

# Parameter: Memory (MB)
memory_limit_cpp = 1000
memory_limit_python = 1000
```

부분을 수정하면 됩니다.

4. result 폴더에서 결과를 확인합니다.

각 폴더마다 나온 output의 내용이, 이름_out.txt 파일에는 결과가 기록됩니다.

## SPJ의 경우

spj.cpp 파일을 직접 작성해야 합니다. 정답이 아닌 경우 0이 아닌 값이 return 되도록 코드를 작성해주세요.

이후 judge.py 파일에서 special judge라고 표시된 3부분을 바꾸어주면 됩니다.

## 예시

예시 파일과, 해당 파일을 source 폴더에 넣고 프로그램을 실행하였을 때의 결과를 수록하였습니다.

주어진 데이터를 정렬하는 문제이며, 각각의 코드의 특징은 아래와 같습니다.

test1: 정답 코드 (cpp)

test2: 정답 코드 (python)

test3: 컴파일 에러 (CE)

test4: 런타임 에러 (RTE)

test5: 시간 초과 (TLE) (제곱 시간 정렬 알고리즘)

test6: 틀렸습니다 (WA)

test7: 메모리 초과 (MLE)