# Hash

데이터를 관리하고, 유지하는 자료구조이다. 리소스를 이용한 속도를 중시한!! 자료구조.

data ---해시함수---> index, value가 들어있는 HASH table!

리소스를 이용해 속도를 중시한다는게 구체적으로 어떤 뜻일까?

바로 일정한 어떠한 값 하나를 찾기 위하여 값을 모두 O(N) 순회하지 않고 index를 통해 해당 값에 더 빠르게 접근하게 할 수 있다는 점이다.

## 충돌 대처

하지만, 테이블 형식으로 해쉬함수의 결과값이 들어가게 된다면 이미 index의 value에 값이 존재한다면, 그 index로는 취할 수 없는 문제가 생긴다. 이렇게 하나의 index에 이미 값이 존재하는데 value가 저장되려고하는경우!! 충돌이 일어났다고 하고, 그 충돌에 대한 대처의 방법으로 다음과같은 방법을 취한다.

1. Chaining
    - index 1에 value가 123, 192, 100이 순차적으로 value가 들어가려한다면 이 123 -> 192 -> 100순서로 chaining. 연결해둔다.
2. Linear Probing
    - 이미 만들어놓은 버켓을 이미 소모하자!
    - index 1에는 value가 있는데, 새로운 newValue가 index 1자리에 들어가려한다면 그다음으로 빈 index를 찾아(2던 5던..) 들어간다.
3. Resizing
    - 할당된 공간을 다 써서 들어갈 자리가 없다면 더 큰 테이블공간을 만들어 기존에 존재하던 데이터를 복사하고 재정비를 한다.

## 보안측면에서의 해시

해시함수란, 임의의 길이의 문자열을 받아 고정 문자열로 바꾸어주는 함수이다. 일정한 규칙이 존재함.

-   동일한 input -> 동일한 output
-   input 이 살짝 변경되어도 -> output은 어마무시하게 바뀜
-   항상 H(x)만 작동. H[inverse](x) 불가능

### Rainbow Table Attack

레인보우 테이블(해쉬값, 입력값 연결해놓은 테이블. 동일 input -> 동일 output의 취약점을 찾기위함) 에서 찾아보면 input을 찾을 수 있음.

### Salt

그 Rainbow Table Attack 을 막기위한 문제. H(SALT + pw) 하여 db에 저장하면 위 Attack 에 대비할 수 있다.

특히나 노드에서 지원하는 `pbkdf2` 알고리즘은, **salt라는 문자열**을 이용해, 해시 알고리즘을 반복하여 적용하는 암호화 알고리즘 방식이다.

이름이 salt인 이유는 음식에 추가로 소금을 친다는 ㅎㅎ 의미에서 붙었다고 한다.

해시함수에 대해 알았고, 이를 암호화에 유용하게 사용한다는 것을 알았으니 코드로 적용해보자.

# nodeJS의 `crypto` module

다양한 방식의 암호화를 도와주는 모듈이다. 실제로 고객들의 데이터는 암호화해야한다.

암호방식에는 비대칭 암호방식, 대칭키를 사용하는 대칭키 암호방식이 있는데

여기서 말하는 대칭, 비대칭은 암호화와 복호화가 대칭으로 이루어지는지 비대칭으로 이루어지는지에 관한 이야기이다.

## 1. 비대칭 암호방식

    대표적으로 해쉬함수를 사용한다.

-   암호화된 문자열로만 비교하는 것 ! 고객이 입력한 비밀번호를 암호화 한 상태를 db에 저장!
-   해시기법 사용 : H(ABCDEFG) -> WBVS, H(BSKEMVDKSJ) -> HWKG 이렇게 고정길이 output으로 바꾸어버리는 것

-   해쉬함수는 항상 같은 input -> 같은 output을 내뱉는다.

하지만 이렇게 단순 해쉬함수를 넣어서 암호화를 하게되면, 다른 input A, B가 같은 output C를 갖게되는 경우가 발생한다.

그러한 보안 취약점을 극복하기위한 대안으로 pbkdf2, bcrypt, scrypt라는 알고리즘으로 비밀번호를 암호화하고있다.

```
const crypto = require('crypto');

const pass = '1q2w3e4r';

/*
 * pass --pbkdf2(salt)--> Encrypted pass
 * 요 과정을 1000번 반복한다. (아래의 코드에서는)
 */
crypto.randomBytes(64, (err, buf) => {
	const salt = buf.toString('base64');
	console.log('salt: ', salt);
	crypto.pbkdf2('pass', salt, 1000, 64, 'sha512', (err, key) => {
		console.log('password : ', key.toString('base64'));
	});
});
```

-   `createHash(알고리즘)`: 사용할 알고리즘을 넣어준다. md5, sha1, sha256, sha512 등의 방식들이 있는데 md5, sha1 취약점이 발견되었다. trudy에의해 보안이 뚫렸슴!! 그래서 현재는 sha512로 사용하곤한다.
-   `update(문자열)`: 암호화할 문자열을 넣는다
-   `digest(인코딩알고리즘)`: 인코딩할 알고리즘을 파라미터로 넣어준다. 주로 base64, hex, latin1이 사용되는데 그중에 base64의 결과 문자열이 가장 짧아서 자주 사용된다.

## 2. 대칭 암호방식

대칭 암호 방식에서는 `key`가 사용된다. 이떄 사용하는 키는 Encryption, Decryption에 동일하게 사용되는 key이다. 대칭암호방식이므로 대칭키를 사용한다.

[대칭키를 이용한 암호해독방식🔗](https://pongsoyun.tistory.com/112)의 원리, 상세한 원리가 궁금하다면 해당 포스팅을 참고하면 된다!

```
const crypto = require('crypto');

const pass = '1q2w3e4r';

const cipher = crypto.createCipher('aes-256-cbc', 'key');
let result = cipher.update('pass', 'utf8', 'base64');
result += cipher.final('base64');
console.log(`Encryption ${pass} => \t ${result}`);

const decipher = crypto.createDecipher('aes-256-cbc', 'key');
let result2 = decipher.update(result, 'base64', 'utf8');
result2 += decipher.final('utf8');
console.log(`Decryption ${result} => \t ${pass}`);


```

같은 key에 대해 input -> output, output -> input이 동일한 모습을 볼 수 있다.

-   `crypto.createCipher(암호화 알고리즘, 대칭키)`
-   `cipher.update(암호화할 문자열, 문자열 인코딩 방식, 출력결과물 인코딩방식)` : 문자열은 `utf8`인코딩, 암호는 `base64`를 많이 사용한다
-   `cipher.final(출력 인코딩)` : 출력결과물의 인코딩. 결과를 문자로 보여야하니 수정
-   `crypto.createDecipher(암호화 알고리즘, 대칭키)` : 암호화할떄 사용했던 알고리즘, 대칭키 넣어줌
-   `decipher.update(암호 문자열, 문자열 인코딩방식, 복호화할 인코딩방식 )` : `cipher.update`때와 반대로 적어주면 된다. originString, utf8, base64 -> result, base64, utf8
-   `decipher.final(출력 인코딩)` : 복호화 결과물의 인코딩. 결과를 문자로 보여야하니 수정
