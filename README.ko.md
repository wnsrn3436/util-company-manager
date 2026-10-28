# Company Manager

[English](README.md)

정직원과 아르바이트 직원을 등록하고 사원번호로 조회하거나 부서별·급여 순으로 출력하며 신분변동을 처리하는 C 콘솔 프로그램이다. 직원 정보는 `CompanyDB.txt` 에 저장된다. 원소 크기만 알면 어떤 구조체든 담는 리스트와 문자열 키 사전을 C 로 직접 만들고, 구조체에 함수 포인터를 붙여 객체처럼 쓰는 구조로 짰다. 학교 과제다.

<p>
  <img src="docs/screenshots/screenshot-1.png" width="480" alt="메인 메뉴">
</p>


## 사용 방법

Releases에서 받아 실행하면 된다. `메뉴 명령어 :` 뒤에 명령어를 입력하고 Enter 를 누른다. 각 화면의 작업이 끝나면 다시 `메뉴 명령어 :` 가 나오는데 여기서 `back` 을 입력하면 메인 메뉴로 돌아간다.

| 명령어 | 동작 |
|---|---|
| `a` | 사원번호로 직원정보 조회 |
| `b` | 부서를 골라 그 부서의 정직원 명단 출력 |
| `c` | 정직원은 직급과 호봉이 높은 순, 아르바이트는 시간당급여가 높은 순으로 출력 |
| `d` | 신입직원 등록 |
| `e` | 사원번호로 찾은 직원의 메모, 부서, 직급, 호봉을 다시 입력 |
| `f` | 종료 |

사원번호는 세 글자다. 정직원은 `R`, 아르바이트는 `A` 뒤에 01 부터 99 까지의 두 자리 숫자를 붙인다 (`R01`). 신입직원 등록에서는 다음 항목을 차례로 묻는다.

| 항목 | 입력 |
|---|---|
| 이름 | 1 에서 10바이트 (한글은 다섯 글자) |
| 성별 | `M` 남성, `F` 여성 |
| 직원상태 메모 | `Y` 면 메모를 입력하고 `N` 이면 대신 휴가가능일이 정해진다 |
| 소속부서 (정직원) | `A` 경리부, `B` 사업부, `C` 마케팅부, `D` 기획실, `E` 홍보부 |
| 직급 (정직원) | `0` 대표이사, `1` 부장, `2` 차장, `3` 과장, `4` 대리, `5` 사원 |
| 호봉 (정직원) | `A` 6호봉 부터 `F` 1호봉 까지 |
| 근무시간, 시간당급여 (아르바이트) | 0 이상의 정수 |

등록할 때 정해지는 휴가가능일은 정직원이 10 에서 직급 번호를 뺀 값(대표이사 10일, 사원 5일)이고 아르바이트가 1일이다. 새 직원은 `CompanyDB.txt` 끝에 덧붙고 신분변동 뒤에는 파일 전체를 다시 쓴다. 프로그램을 켜면 이 파일을 읽어 목록을 채운다.


## 구현 원리

**리스트는 원소 크기로 움직인다.** `List` 는 `void *` 버퍼와 원소 크기를 들고 있다가 추가할 때 원소를 `memcpy` 로 통째로 복사해 넣는다. 처음 용량은 2이고 가득 차면 두 배 크기의 버퍼를 새로 잡아 옮긴다. 직원 목록은 `NewList(sizeof(Employee))` 로, 사전 안의 키-값 쌍 목록은 `NewList(sizeof(KeyValuePair))` 로 만든다.

```c
memcpy((byte *)(list->Item) + (list->Count * list->ItemSize), value, list->ItemSize);
++(list->Count);
```

**사전은 리스트 위에 얹었다.** `Dictionary` 는 `String` 키와 값의 사본을 담은 `KeyValuePair` 를 리스트에 넣고, 찾을 때는 처음부터 `strcmp` 로 키를 비교한다. 같은 키가 이미 있으면 추가하지 않는다.

**구조체에 함수 포인터를 붙여 객체처럼 쓴다.** `NewList`, `NewDictionary`, `NewMenu`, `NewCompany` 같은 생성 함수가 구조체를 할당하고 `_ListAdd` 같은 구현 함수를 필드에 연결한다. 호출은 `company->IndexOf(company, search)` 처럼 자기 자신을 첫 인자로 넘기고, `Dispose` 가 안쪽 메모리까지 풀어 준다.

**메뉴는 명령어 사전이다.** `Menu` 는 명령어 문자열을 콜백 함수 포인터에 연결한 사전을 화면 글과 함께 갖는다. 메인 루프는 입력한 명령어로 사전을 찾아 나온 함수를 부르기만 하고, 각 콜백이 사전을 비운 뒤 그 화면에서 받을 명령어를 새로 등록한다.

```c
void(*callback)(Menu *, Company *) = menu->Command(menu, command);
if (callback != NULL)
{
	system("cls");
	callback(menu, company);
}
```

**직원 정보는 태그로 갈리는 공용체다.** 정직원의 부서, 직급, 호봉과 아르바이트의 근무시간, 시간당급여는 한 공용체에 겹쳐 있고, 사원번호 첫 글자가 어느 쪽인지 정한다. 메모와 휴가가능일도 공용체이고 `TypeTag` 값(`HAS_STRING`, `HAS_INT`)으로 구분한다. 파일에 쓰고 읽을 때도 메모 태그와 사원번호 첫 글자를 보고 한 줄의 형식을 바꾼다.


## 파일

| 경로 | 내용 |
|---|---|
| `source/Company Manager.sln` | Visual Studio 2015 솔루션 |
| `source/Company Manager/Main.c` | 메인 루프, 화면별 콜백, 항목 입력 |
| `source/Company Manager/List.c` | 원소 크기로 다루는 동적 배열 |
| `source/Company Manager/Dictionary.c` | 문자열 키 사전 |
| `source/Company Manager/Menu.c` | 화면 글과 명령어 사전 |
| `source/Company Manager/Company.c` | 직원 목록, 파일 저장과 불러오기 |
| `source/Company Manager/Employee.c` | 직원 출력, 부서·직급·호봉 이름 |
| `source/Company Manager/InputExt.c` | 검사를 통과할 때까지 다시 받는 입력 함수 |
| `source/Company Manager/StringExt.c` | `String` 구조체와 숫자, 대문자, 소문자 검사 |
| `source/Company Manager/TypeTag.h`, `source/Company Manager/Byte.h` | 공용체 태그와 `byte` 형 |
| `docs/screenshots/` | 스크린샷 |
| Releases | 실행 파일 |


## 라이선스

zlib 라이선스다. 자세한 내용은 [LICENSE](LICENSE) 에 있다.
