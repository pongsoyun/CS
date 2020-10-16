# Index

-   [6. 검색조건 지정하기](#6._검색조건_지정하기)
-   [7. 조건 조합하기](#7.-조건-조합하기)
-   [8. 패턴매칭에 의한 검색](#8.-패턴-매칭에-의한-검색)
-   [9. 정렬 - ORDER BY](#9.-정렬-order-by)
-   [10. 복수의 열을 지정해 정렬하기](#10.-복수의-열을-지정해-정렬하기)
-   [11. 결과 행 제한하기 LIMIT](#11.-결과-행-제한하기-limit)
-   [12. 수치 연산](#12.-수치-연산)
-   [13. 문자열 연산](#13.-문자열-연산)
-   [14. 날짜연산](#14.-날짜연산)
-   [15. case문으로 데이터 변환하기](#15.-case문으로-데이터-변환하기)
-   [16. 행 추가하기 - INSERT](#16.-행-추가하기-insert)
-   [17. 삭제하기 - DELETE](#17.-삭제하기-delete)
-   [18. 데이터 갱신하기 update](#18.-데이터-갱신하기-update)
-   [19. 물리삭제와 논리삭제](#19.-물리삭제와-논리삭제)
-   [20. 행 개수 구하기 - COUNT](#20.-행-개수-구하기-count)
-   [21. COUNT 이외의 집계함수](#21.-count-이외의-집계함수)
-   [22. 그룹화 GROUP BY](#22.-그룹화-group-by)
-   [23. 서브쿼리](#23.-서브쿼리)
-   [24. 상관 서브쿼리](#24.-상관-서브쿼리)
-   [25. 데이터베이스 객체](#25.-데이터베이스-객체)
-   [26. 테이블 작성, 삭제, 변경](#26.-테이블-작성,-삭제,-변경)
-   [27. 제약](#27.-제약)
-   [28. 인덱스 구조](#28.-인덱스-구조)
-   [29. 인덱스 작성과 삭제](#29.-인덱스-작성과-삭제)

```
mysql -uroot -p
show databases;
show tables;

create databases study_db default character set utf8;
create table numberTable
(
    no int,
    name varchar(32) not null,
    alias varchar(32),
);

# int형 phoneNumber attributes(column. 행) 추가
alter table numberTable add phoneNumber int default 1;

# 다중 삽입
insert into numberTable values(3, 'c', 'chicken', 12), (4, 'd', 'duck', 2);

```

### table 구조 참조하기

field, type ... null, key, default, extra 등의 값을 보여줌

```
desc worklist;

select \* from \_tableName;
select \_fieldName from \_tableName;
```

### 자료형

-   char형 : 고정길이문자열. 열의 최대 길이를 정해야함 ex. char(10) : 10글자까지만 저장가능 ex. char(5) = 'abc\_\_'
-   varchar형 : 가변길이문자열. ex. varchar(5) = 'abc\_'

char형 'abc' != varchar형 'abc'

# 6. 검색조건 지정하기

select team, worker from worklist where worker='pingpong';
select worker, todo from worklist where date>'2020-01-01';

-   where (행 -> 세로 쫙 핀 index중 어떤애 선택할거니?)
    where 구의 조건에 일치하는 행만 결과로 반환! 열과 연산자, 상수로 구성되는 식

    ```
    # 다중 where
    select name from animal_ins where name like '%el%' and animal_type = 'Dog' order by name;

    # 'hyunwoo'가 아닌 worker만 필터링
    select * from worklist where worker<>'hyunwoo';
    ```

    ### NULL값 검색

    ```
    # NULL로 삽입 가능
    insert into student values(123123, 'anotherPerson', NULL, NULL);

    # where major=null 안됨! is null로 찾기
    select * from student where major is null;

    # 🔥 데이터가 Null 일 경우 데이터를 치환해야 할 때 coalesce를 사용할 수도 있다.
    select *, ifnull(name, 'No name') name from animal_ins;
    ```

-   select (열 -> 항목중 어떤애 선택할거니?)

# 7. 조건 조합하기

and, or, not으로 조합해 검색

```
# <> : not
select * from student where grade<>'A'
    and major='글로벌미디어학부';
```

# 8. 패턴 매칭에 의한 검색

`LIKE`를 사용하여 부분 검색(패턴 매칭). 정규식(regex) 사용할 수 있음

사용할 수 있는 메타문자

-   `%` : 0~n개 비었음
-   `_` : 1개 비었음

```
# 열 LIKE 패턴
select * from worklist where worker like '%pong%'; # pingpong (O)
select * from worklist where worker like '_pong' ; # pingpong (X)
select * from worklist where worker like '____pong'; # pingpong (O)

select * from worklist where todo like '%기획%'; # 기획회의 (O), 기획 개발 디자인 (O), 오늘기획 피드백(O)
select * from worklist where todo like '기획%'; # 기획회의 (O), 기획 개발 디자인 (O), 오늘 기획 피드백(X)

```

문자열에 `%, _`가 들어가있을 경웨는 escape. `\%, \_`로 사용하면 됨.
it`'`s 또한 `" ' "` || `'\''`이렇게 똑같이 해주면 됨

```
insert into worklist values('anonymous', 'pongping', "it's beautiful day!", '2020-07-29');
insert into worklist values('anonymous', 'pongping', 'it\'s beautiful day!', '2020-07-29');
```

# 9. 정렬 ORDER BY

주의해야 할 점은, `varchar` 형으로 되어있는 숫자값의 경우에는 문자로 판단하여 진행하므로 1 2 10 12 로 정렬되는것이 아니라, 1 10 12 2 순으로 정렬됨에 유의하자!

원본 변경 X

```
select * from worklist where team = '언행일치' order by date;
select * from worklist order by date;

select * from worklist order by date desc; # 내림차순
select * from worklist order by date asc; # 오름차순

# name: asc => date: desc (이름 같은애들끼리는 date 더 늦은애가 먼저 나옴)
select * from worklist order by name, date desc;

```

# 10. 복수의 열을 지정해 정렬하기

```
# no먼저 정렬 -> phoneNumber 그다음에 정렬
select * from numberTable order by no, phoneNumber;

# phoneNumber 정렬 -> 그다음에 no 정렬
select * from numberTable order by phoneNumber, no;

# 정렬방법 지정하기 ( desc, asc[default] )
select * from numberTable order by no desc, phoneNumber asc;
```

참고로 null값을 가장 작은 값으로 취급해, asc에서는 가장 먼저, desc 에서는 가장 나중에 표시함

# 11. 결과 행 제한하기 LIMIT

```
# name 열에 abcde가 있으면, 3개까지 뽑는데 시작행=2 부터. name 열의 3, 4, 5
select name from numberTable limit 3 offset 2;

# 조건문과 함께 사용하기
select * from numberTable where alias is not null limit 2;

# 정렬과 함께 사용하기
select * from numberTable order by no desc limit 3;

# 첫 행만 뽑기
select name from animal_ins order by datetime limit 1;
```

### offset 지정하기

이 offset 기능을 언제 사용하냐.. 바로 웹에서 대량의 데이터를 한 페이지에 다 로드할 수 없을 때, page 1, 2, 3, ... 별로 나누어 로드한다. 그때 offset을 사용해주면 된다.

# 12. 수치 연산

```
# price*quantity 열 추가하기 -> 원본 손상 X
select *, price*quantity from mart;

select *, quantity+name from mart; # 하면 숫자만 보여지게됨. String으로 자동형변환 그런거없음!

# alias 추가하기
select *, quantity*price as total from mart;
select *, quantity*price as '예상 매출' from mart;

# 조건식과 같이 검색해 테이블 뽑아내기
select *,
    price*quantity as total from mart
    where price*quantity>20000; // (O)
select *,
    price*quantity as total from mart
    where total>20000; // (X) : unknown column

```

total이 존재하지 않는다는 에러가 뜨는 이유는, Db서버 내부에서 **where구 처리 -> select 구** 순서로 처리되기 때문이다.

1. where구 -> 행 추출
2. select 구 -> 열을 선택해 별명 붙이기

```*
# 정렬하기
select *,
    price*quantity as total from mart
    order by price*quantity desc; // (O)
select *,
    price*quantity as total from mart
    order by total desc; // (O)
```

정렬은 또 total이 사용 가능한 이유는, **select -> order by**이기 때문이다.

> 곧 순서가 **where -> select(alias) -> order by** 로 db서버 내부에서 동작한다.

### `"` vs `'` convention

-   `"` : 데이터베이스 객체 명. 숫자로 시작하지 않도록 하자
-   `'` : 문자열 상수

### 함수로 연산하기

-   산술 함수
-   ROUND 함수 :

```
select * from mart where mod(no, 2)!=0; # mod연산. no행%2 의 값이 0이 아닌경우만 뽑아 테이블 리턴
select * from mart where mod(no, 2)=0; # mod연산. no행%2 의 값이 0인 경우만 뽑아 테이블 리턴

# ROUND 함수(반올림)
alter table mart add amount float default 3.786;
select *, round(amount) as amount from mart; // 4
select *, round(amount, 1) as amount from mart; // 3.8
select *, round(amount, 2) as amount from mart; // 3.79

select no, name, price, round(price, -3) from mart; // 3300 -> 3000, 1500 -> 2000, 1300 -> 1000
```

# 13. 문자열 연산

-   `concat()`
-   `substring(start, cnt)`: start 자리부터(start-1 = index) cnt 개수만큼
-   `trim()`: 문자열 앞뒤에 여분의 space가 있으면 제거해줌(중간에있으면 제거X)
-   `character_length()`: 문자열 길이 리턴
    -   varchar 형의 문자열은 가변길이라, 길이가 서로 다름

```
# 1. concat
select concat(name, alias) from numberTable; # String + String
select concat(name, no) from numberTable; # String + Number

# alias 가능
select concat(name, alias) as secondName from numberTable; # String + String

# 2. substring
select substring(alias, 1, 4) from numberTable; # 앞에서부터 4글자만 보임

select *, concat('입학년도: ', substring(student_ID, 1, 4)) as 입학년도리스트 from student; # 이렇게 같이 쓸수있음

# 3. trim
select *, trim(name) as trimName from student;

# 4. character_length
select *, character_length(name) as length from student;


```

# 14. 날짜연산

-   `current_date` + `interval 1 day` : 현재+1일

```
# 표준sql로 지정되어있는 함수. system의 현재 시간알려줌
select current_timestamp;
select current_date + interval 1 day; # 2020-07-30 +1
select current_date - interval 1 day; # 2020-07-30 -1
```

# 15. case문으로 데이터 변환하기

```
case when 조건식1 then 식1
    when 조건식2 then 식2
    else 식3
end


select *,
    case when team='모름'
    then 'anonymous team'
    else team
    end 'team alias'
from worklist;


# NULL 값을 변환하는 경우
select *, coalesce(alias, 'untitled') from numberTable; # alias열에서 null -> 'untitled'로 변경
```

-   디코드 : 코드=수치데이터(1/2) -> 정보(남/여)
-   인코드 : 코드=수치데이터(1/2) <- 정보(남/여)

```
when a = 1 then '남자'
when b = 2 then '여자'

select *,
    case when a=1 then 'man'
    then a=2 then 'woman'
    else 'it'
end as 'gender' from membership;

```

### 주의사항!

else를 안해주면, 나머지 항목이 모두 null 이 되므로

```
# 이렇게 해주면 첫번째 말고 나머지 모두 null이아니라 원래의 no값
select *, case when no=1 then 'first' else no end from numberTable;

# 일반적인 경우의 사용
select *, case
    when a = 1 then 'man'
    when a = 2 then 'woman'
    when a is null then '데이터 없음'
    else '미지정'
end as 'gender' from numberTable;

```

# 데이터의 추가, 삭제, 갱신

# 16. 행 추가하기 insert

```
# insert로 행 추가하기
insert into mart values(4, 'basil', 4200, 24);

# 값을 저장할 열 지정하기
insert into mart(name, price) values('flour', 3000);

# default 값으로 저장하기
insert into mart values(5, 'tissue', 5000, 24, default);

```

# 17. 삭제하기 delete

```
delete from mart where no is null;

# 모든 행(data) 모두 삭제
delete from mart;

delete from mart where no=1 or no=2;

```

# 18. 데이터 갱신하기 update

시스템 다루다가 갱신해야할 때 update 하거나, 변경된 값을 update 한다

```
# 모든 행 update
update mmart;

# where 에서 찾은 행에 price열에 4100을 넣을거임!(set)
update mart set price = 4100 where name='tissue';

# 모든 행의 amout 값을 5.2로 update
update mart set amout = 5.2;

# update로 현재 value에 연산 넣기
update mart set price = price + 1000;

# quantity -> amount 순으로 갱신
update mart set quantity = quantity + 5, amount = price/quantity;

# null 초기화
update mart set amout = null; # 당연히 Not null 이면 xxxx

```

# 19. 물리삭제와 논리삭제

데이터를 삭제하는 두가지 방식이 있다.

-   물리삭제 : 일반적인 삭제방법. 직접 delete 명령어를 통해 테이블에서 삭제해버리자!
    -   `delete`
-   논리삭제 : 삭제된 것 처럼 보여지게, 해당 삭제하려는 애를 삭제한 척 하고 테이블을(삭제 플래그 등을 이용) 리턴하자!
    -   장점 : 원본의 사본을 만들어 해당 데이터를 삭제하므로 원본을 유지할 수 있음
    -   단점: db테이블이 결과적으로 하나 더 생기는것때문에 용량이 증가 -> 검색 속도가 떨어짐
    -   `update`로 구동
    -   내부적으로 : 삭제flag = 1로 만들고 => select from xxxx where 삭제flag<>1; 해서 테이블의 사본을 리턴

### 그렇다면 언제 어떤삭제를 사용하는 것이 좋을까?

1. 물리삭제

    - sns 서비스에서 사용자가 탈퇴한 경우

2. 논리삭제
    - 사용자가 주문을 취소하는 경우(주문을 했던 내역을 아예 삭제하면 안되는 경우 -> 주문관련 통계를 낼수도 있고, 해당 내역은 보여져야 정상)

등이 있다. 정리해서, 물리삭제는 원본데이터싸그리 삭제, 논리삭제는 내역은 남아야하는 경우를 말한다.

# 5장. 집계와 서브쿼리

# 20. 행 개수 구하기 count

집합에서 `count`, `sum`, `avg`, `min`, `max` 등의 집계함수를 이용하여 일정 행의 개수/합/... 등을구할 수 있다.

-   집계 : 집합으로부터 하나의 값을 계산 하는 것(1개의 값이 되는 것)

-   `count`: 행 개수 구하기

    -   \*를 인수로 사용할 수 있음
    -   `distinct` : 중복 제거

```
# COUNT : 행 개수 구하기
select count(*) from mart; # 5
select count(amount) from mart; # amount는 전체행이 모두 null 값이라 0

# where로 구 지정하기
select count(*) from mart where price>3000;
# select *, count(*) from mart where price>3000; # XXXXXX 이거 안됨 ERROR ! 집계함수이기 때문(하나의 값으로 나와야함)
select count(*), count(name), count(amount) from mart; # 5 5 0

# distinct로 중복 제거
select distinct quantity from mart;

# quantity 열의 중복 허용, 중복 제거 행의 계수를 구하는 집계함수 count의 사용
select count(all quantity), count(distinct quantity) from mart;
select count(quantity), count(distinct quantity) from mart;
```

# 21. count 이외의 집계함수

```
select sum(price) from mart;
select sum(price) from mart where quantity<30;

# avg로 평균내기
select avg(price) from mart;
select sum(price)/count(price) from mart;

# avg로 null -> 0으로 변환 후 평균내기
select avg(case when no is null then 0
            else no end) as newNO from mart;

# min, max로 최대/최소 구하기
SELECT MIN(PRICE), MAX(PRICE) FROM MART;
```

# 22. 그룹화 group by

그룹화를 통해 집계함수의 활용 범위를 넓힐 수 있다.

그룹화 하면 지정된 열의 값이 같은 행이 하나의 그룹으로 묶인다. 같은 4라는 값이 여러개인 행들은 모두 그룹화 되어 하나의 행으로 보여지는 것!

```
# distinct === group by 와 같은 결과
select name from mart group by name; # name이 같은행이 여러개였다면 하나로만 보여짐
select distinct name from mart;

# quantity 열을 그룹화해 계산하기
select quantity, count(quantity), sum(price) from mart group by quantity;
+----------+-----------------+------------+
| quantity | count(quantity) | sum(price) |
+----------+-----------------+------------+
|       36 |               1 |       4300 |
|       27 |               1 |       2500 |
|       19 |               1 |       2300 |
|       29 |               2 |       9300 |
|       10 |               1 |       1700 |
|        2 |               1 |       1100 |
+----------+-----------------+------------+

quantity = 29 인 행이 2개여서, count의 결과가 2가 나오고, 각 물건의 값이 4200, 5100 이라 9300이 나옴 !

```

### 집계함수를 사용할 경우 having 구로 검색 조건 지정

집계함수는 where 구의 조건식에서는 사용할 수 없다. select 다음에서만 사용할 수 있음 !
왜냐, 내부 처리 순서가

> where -> group by -> having -> select -> order by

이기 때문.

-   3. **select** name from mart
-   1. **where** price>2000
-   2. **group by** name
-   4. **order by** name;

그래서 조건식을 사용하여 select 를 할 경우에는 `having`구를 이용하여 조건식이 참인 그룹값만 클라이언트에 반환된다.

1. where로 검색
2. 검색 후 그룹화
3. having count(name) = 1 인 애들 찾기

```
select name from mart
    where price>2000
        group by name
            having name='potato';

select quantity, count(quantity) from mart group by quantity having quantity>20;
# select quantity as q, count(quantity) as qCnt from mart group by q having q>20;
```

> where -> group by -> having -> select -> order by

순서로 작동하므로, select 구보다 먼저 처리되므로 별명(alias)을 사용할 수 없다.
mysql에서는 가능하지만, oracle에서는 에러가 발생하는 점 알아두자.

### 여러 개의 열의 그룹화

**group by로 그룹화 하는 열들만! select 구에 기술할 수 있다**

```
select name, quantity from mart group by quantity having quantity>20; # xxxxxx
select name, quantity from mart group by name, quantity having quantity>20;  # OOO

# 집계함수를 사용하면 하나의 값이므로 괜찮음
select min(quantity), name, sum(quantity) from mart group by name;
# 둘다 똑같은 quantity를 가져오는 사용이지만, 의미가 좋은 코드는 아닌듯 함
+---------------+---------+---------------+
| min(quantity) | name    | sum(quantity) |
+---------------+---------+---------------+
|            36 | potato  |            36 |
|            27 | chips   |            27 |
|            19 | balloon |            19 |
|            29 | basil   |            29 |
|            29 | tissue  |            29 |
|            10 | bread   |            10 |
|             2 | onion   |             2 |
+---------------+---------+---------------+


# 결괏값 정렬
select name, quantity from mart group by name, quantity having quantity>2000 order by name desc;
```

# 23. 서브쿼리

select 명령에 의한 데이터 질의로, 부수적인 부분을 말한다. where, select, delete, update 구 등

```
# 1. delete 의 where 구에서 서브쿼리 사용하기
delete from mart where no is null;

# 변수로 사용하기
set @minQuantity = (select min(quantity) from mart);
delete from mart where quantity = @minQuantity;

```

### 일반적인 서브 쿼리 패턴

서브쿼리를 사용할 때는 그 select 명형이 어떤 값을 반환하는지 주의해야한다.
일반적으로 서브쿼리는 '하나의 항목'으로 취급한다. 문법적으로는 문제가 없지만 실행하면 에러가 발생하는 경우가 잦은데, 그 상황은 스칼라 값의 변환이 되어있지 않기 때문에 발생하는 에러인지 확인해보아야한다.

1. 하나의 값을 반환(스칼라 값)  
   -> 스칼라 값끼리 비교연산을 할 수 있다 (where a = ~~~ )
2. 복수의 행이 반환되지만 열은 하나인 패턴
3. 하나의 행이 반환되지만 열이 복수인 패턴
4. 복수의 행, 복수의 열이 반환되는 패턴

```
# 1. 하나의 값을 반환(단 하나의 스칼라 값)
select min(quantity) from mart;

# 2. 복수의 행이 반환되지만 열은 하나인 패턴
select quantity from mart;

# 3. 하나의 행이 반환되지만 열이 복수인 패턴
select min(no), max(quantity) from mart;

# 4. 복수의 행, 복수의 열이 반환되는 패턴
select no, quantity from mart;
```

```
# select 구에서 서브쿼리 사용하기
select
(select count(*) from mart) as martCnt,
(select count(*) from numberTable) as numberCnt;

# set 구에서 서브쿼리 사용하기

# from 구에서 서브쿼리 사용하기
# 괄호로 select 구를 묶으면 되지만, from구는 table을 지정하는 만큼! (from tableName) 스칼라 값이 아니어도 괜찮다.!!!
select * from (select quantity from mart) sq; # sq: Sub Query (alias)
select * from (select quantity from mart) as sq;

#실제 사용
select *from (
    select * from mart order by quantity desc
) sq
where quantity <= 20 ;


# insert 명령과 서브쿼리
insert into sample541 values(
    (select count(*) from 51),
    (select count(*) from 54)
); # 이 코드는 sample541 테이블이 (int, int) 여야겠지 물론!

# insert select
insert into sample541 select 1, 2; # insert into sample541 values(1,2);

# 열 구성이 똑같은 테이블 사이에는 insert select 명령으로 행을 복사할 수도 있음
insert into sample542 select * from sample543;
```

# 24. 상관 서브쿼리

서브쿼리를 이용해 delete, select를 결합해 사용했다.
그리고 스칼라 서브뭐리로 사용한다는 것도 알았다.

서브쿼리의 일종인 '상관 서브쿼리'를 `exists`로 조합시켜 서브쿼리를 사용해보자!

-   상관 서브쿼리 : 부모 명령과 자식인 서브쿼리가 특정 관계를 맺는 것

```
# 1. exists
update sample551 set a = '있음' where
    exists (select * from sample552 where no2 = no);

# not exists
update sample551 set a = '없음' where
    not exists (select * from sample552 where no2 = no);

# 상관 서브쿼리 : 부모 명령과 자식인 서브쿼리가 특정 관계를 맺는 것
# 열에 이름 붙이기
update sample551 set a = '있음' where
    exists (select * from sample552 where sample552.no2 = sample551.no);

# in : or을 사용하는 경우와 의미는 같지만, 조건식이 깔끔해진다 -> 스칼라 값으로 변경
select * from mart where quantity  = 19 or quantity = 29 ;
select * from mart where quantity in (19, 29); # 둘은 같은 의미

# 스칼라 값을 비교하여 선택하기
select * from sample551 where no in
    (select no2 from sample 552);

select * from sample551 where no not in
    (select no2 from sample 552);
```

# 6. 데이터베이스 객체 작성과 삭제

# 25. 데이터베이스 객체

데이터베이스 객체란, 테이블, view, index 등 DB내에 정의하는 모든것을 일컫는 말이다. oop의 객체개념이 아니라, db내의 객체라는 의미로 데이터베이스 객체. 라는 말이 붙은 것이다.

> 데이터베이스 내부에 실체가 있다면 그것이 바로 객체!

ex. 테이블, 뷰, 인덱스 : 데이터베이스 내에 실체를 가짐 -> 데이터베이스 객체 ㅇㅇ
명령 : 데이터베이스 내에 실체가 없음 -> 데이터베이스 객체 ㄴㄴ

### 스키마(schema)

데이터베이스 객체는 스키마라는 그릇 안에 만들어지므로, 스키마가 다르면 서로 이름이 같아도 상관 없다. 그래서 데이터베이스 객체는 스키마 객체라고 불리기도 한다.

```
# study_db 라는 schema를 생성
create database study_db;

# schema안에 table을 생성
create table numberTable
(
    no int,
    name varchar(32) not null,
    alias varchar(32),
);
```

schema, table은 namespace 이기도 함!

# 26. 테이블 작성, 삭제, 변경

```
# calendar 테이블 생성(작성)
create table calendar (
    month int,
    date int not null,
    title varchar(32) default 'untitled'
);

# 테이블 삭제
drop table newMart;

# 테이블은 그대로 두고 모든 행 삭제
turncate table newMart;

# 테이블 변경
# soldOut이라는 열을 추가
alter table newMart add soldOut varchar(32) default 'no' ;

# 열 속성을 변경
alter table newMart modify amount int default 0;

# 열 이름 변경
alter table newMart change amount store;
# 열 이름 변경 + 열 속성 변경
alter table newMart change amount store varchar(32) defualt 'origin store';

# 열 삭제
alter table newMart drop store;
```

-   `drop table` : db에서 테이블, 데이터를 삭제
-   `delete where~~` : 테이블은 그대로 두고 테이블에서 where에 해당하는 Data를 삭제
-   `turncate table` : ddl로 분류되는 명령어, 모든 행을 삭제 할 때 빠르게 삭제

### 실무에서 사용하는 `alter table` - 최대 길이 연장

대규모의 db에서는 데이터의 크기가 매우 커지는 경향이 있다. 특히나 행개수가 많은 테이블에서는 데이터 하나의 크기를 최적화 하는 것 만으로도 저장 공간을 줄일 수 있는데,
이떄 데이터의 크기가 늘어날 때 alter table로 열의 자료형만 변경해 대응할 수 있다.

```
alter table newMart modify name varchar(32);

```

일반적으로 줄이는 경우는 거의 없다. (데이터가 잘릴 위험이 있으므로)

### 열 추가

시스템의 기능 확장등으로 인해 열을 자주 추가한다. 사실 이 행위는 테이블의 정의가 바뀌어버리는 만큼 영향을 크게 줄수있으므로 (insert 등...) 에러감지에 특히나 유의해야한다.

```
alter table newMart add stores varchar(20) default 'origin store';
alter table newMart add openYear int default 2020;
```

# 27. 제약

테이블에 설정하는 것

```
create table calendar
(
    month int not null default 1,
    date integer not null unique,
    title varchar(10) default 'untitled',
    # 테이블에 '테이블 제약' 정의하기
    # primary key (month, date)
    # 제약에 이름붙이기
    constraint pkey_sample primary key (month, date)
)

# 열 제약 추가
alter table calendar modify title varchar(30) not null;

# 테이블 제약 추가
alter table calendar add contraint pkey_id primary key(id);
+-------+-------------+------+-----+----------+-------+
| Field | Type        | Null | Key | Default  | Extra |
+-------+-------------+------+-----+----------+-------+
| month | int(11)     | YES  |     | NULL     |       |
| date  | int(11)     | YES  |     | NULL     |       |
| title | varchar(32) | YES  |     | untitled |       |
| id    | int(11)     | NO   | PRI | NULL     |       |
+-------+-------------+------+-----+----------+-------+

# 제약 삭제

# not null 제약 없애기 : 그냥 재정의 해주기
alter table calendar modify id varchar(10);

# 테이블 제약 삭제
alter table calendar drop constraint pkey_id; #error
alter table calendar drop primary key; # 테이블에 primary key는 하나일것이므로 괜츈
```

### 기본키

-   not null : 열 제약
-   테이블 제약 : 기본키 제약

*   기본키로 지정할 열은 not null 제약이 설정되어있어야함
*   key : 검색할 때의 키워드. 대량의 데이터에서 원하는 데이터를 찾아낼 때 키가 되는 요소를 지정해 검색함.

-   기본키는 테이블의 행 한개를 특정할 수 있는 검색키이다. 기본키로 설정된 열이 중복하는 데이터 값을 가지면 제약에 위반됨! 오직 하나여야만 함.

```
# 테이블 작성하기 : id를 primary key(기본키)로
create table calendar (
    month int(11),
    date int(11),
    title varchar(32) default 'untitled',
    id varchar(10) not null,
    constraint pkey_calendar primary key(id)
);


# 행 추가하기
insert into calendar values(1, 6, "pong's birthday", 'a1');
insert into calendar values(11, 12, "yoon's birthday", 'b1');


# 중복하는 행 추가하기 : primary가 겹치면 안됨! => 왜냐하면 **기본키 제약** 때문!
insert into calendar values(1, 14, "hello", 'a1');
# ERROR 1062 (23000): Duplicate entry 'a1' for key 'PRIMARY'

# 갱신도 안됨 => 왜냐하면 *기본키 제약** 때문!
update calendar set id='a1' where id='a2';

```

기본키 제약이 설정된 열에는 중복된 값을 저장할 수 없다.

복수의 열로 기본키를 구성할 수도 있는데, 에를들어 a, b. 2개의 열을 기본키로 설정한다면
+---+---+
| a | b |
+---+---+
| 1 | 1 |
| 2 | 1 |
| 3 | 2 |
| 3 | 3 |
+---+---+
이런 식으로도 가능하다. a와 b 각각의 열에는 중복값이 있지만 a,b의 조합으로는 중복값이 없기 때문

# 28. 인덱스 구조

'색인'이라고도 불리는 index는 db 객체중 하나이다.
차례로 나열되어있어 대량의 데이터를 검색할 때는 이진탐색으로 검색한다.
그런데 더 효율적으로 이진트리를 사용하는데, 거기에는 중복되는 값을 등록할 수 없기 때문에 기본키제약을 갖는 경우에이진트리로 인덱스를 작성하는 데이터베이스가 많다.

# 29. 인덱스 작성과 삭제

```
# 인덱스 작성
# create index 인덱스명 on 테이블명(열명1, 열명2, ... )
create index no on calendar(no);

# 인덱스 삭제
# drop index 인덱스명 on 테이블명
drop index no on calendar;
```

### explain ~~sql명령~~

인덱스 작성을 통해 쿼리의 성능 향상을 기대할 수 있는데, 실제로 index를 사용하여 검색하고있는지를 확인하려면 explain 명령을 사용하면 된다. 상태를 보여주는 명령이라고 생각하면 된다.

```
explain select * from calendar where month = 1;
+----+-------------+----------+------------+------+---------------+----------+---------+-------+------+----------+-------------+
| id | select_type | table    | partitions | type | possible_keys | key      | key_len | ref   | rows | filtered | Extra       |
+----+-------------+----------+------------+------+---------------+----------+---------+-------+------+----------+-------------+
|  1 | SIMPLE      | calendar | NULL       | ref  | calendar      | calendar | 5       | const |    1 |   100.00 | Using index |
+----+-------------+----------+------------+------+---------------+----------+---------+-------+------+----------+-------------+
```

### 최적화

select 명령을 실행할 때 인덱스의 사용여부를 선택한다는 것을 알았다. 이는 db 내부에서 최적화에 의해 처리된다. 바로 **실행계획(`where`조건으로 지정되어있음)**을 세운 후 select 명령을 실행하는 것이다. 그리고 그 실행계획을 explain 명령이 확인한다.
