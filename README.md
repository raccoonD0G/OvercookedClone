# OvercookedClone

Standalone·Listen Server·Dedicated Server를 하나의 코드베이스로 지원하는 Unreal Engine 5 협동 요리 게임입니다.
3인 팀이 '5 Minutes of Overcooked'를 클론했습니다.

- 시연 영상: https://youtu.be/cOFYimPveVQ
- 개발 기간: 2025.05–2025.06
- 기술: Unreal Engine 5 · C++ · Blueprint · Behavior Tree · Online Subsystem Steam

## 담당 범위

3인 팀 프로젝트입니다. 저(raccoonD0G)는 C++ 코드 전체와 블루프린트 일부를 맡았습니다.

## 설계 목표

같은 게임 규칙을 로컬 실행과 서로 다른 서버 구성에서 중복 구현하지 않고 재사용하는 것,
그리고 상호작용과 AI가 네트워크 환경에서도 일관되게 동작하도록 하는 것이 목표였습니다.

- **하나의 로직, 세 가지 실행 모드**: Standalone, Listen Server, Dedicated Server가 같은 게임 로직을 사용합니다. 멀티플레이는 Steam 기반입니다.
- **컴포넌트 기반 상호작용**: 주문 수령, 재료 획득, 주방기구 사용, 쥐 잡기 등 모든 상호작용을 `E` 키 하나로 처리합니다. 이를 `InteractComponent`와 상호작용 인터페이스로 구현했습니다.
- **인터페이스를 참조하는 BT Task**: Behavior Tree Task가 특정 Actor가 아닌 인터페이스를 참조합니다. 그래서 손님·웨이터 AI가 같은 Task를 재사용합니다.
- **델리게이트로 참조 흐름 정리**: 시스템 간 직접 참조 대신 델리게이트로 이벤트를 전달합니다.
- **설계 회고**: Player를 Pawn·PlayerController·PlayerState로 관리하듯, AI도 Pawn·AIController·AIState로 나눠 봤습니다. 이 구조는 응집도를 떨어뜨리는 비효율적인 설계였습니다. 그래서 재사용 가능한 Task 중심으로 조정했습니다.

## 게임 구성

| 요소 | 동작 |
|---|---|
| 플레이어 | `WASD` 이동, `E` 상호작용 |
| 계산대 | 상호작용하면 플레이어에게 만들 요리를 할당 |
| 냉장고 | 레시피에 필요한 식재료 중 하나를 무작위로 건네줌 (들고 있던 재료는 교체) |
| 주방기구 | 플레이어가 든 식재료의 상태를 바꿈 |
| 완성 스테이션 | 모은 재료로 음식을 완성하고, 성공하면 웨이터를 부름 |
| 손님 | 입구에서 주기적으로 생성 → 계산대에서 주문 → 빈 테이블에 착석 |
| 웨이터 | 완성된 음식을 손님 테이블로 운반 |
| 손님 테이블 | 손님 한 명당 하나를 할당 |

## 코드 구조

`Source/OvercookedClone/`

| 폴더 | 내용 |
|---|---|
| `Actors/` | 계산대, 냉장고, 주방기구, 완성 스테이션, 손님 테이블, 스포너 |
| `AI/Tasks/` | 재사용 가능한 Behavior Tree Task |
| `AIControllers/`, `AIStates/` | 손님·웨이터·쥐 AI |
| `Interfaces/` | 상호작용·이동·주문·식사 인터페이스 |
| `Components/` | 상호작용, 타이머 컴포넌트 |
| `GameModes/`, `GameStates/`, `PlayerControllers/`, `PlayerStates/` | 팀 빌딩 → 주방 → 결과 흐름 |
| `Subsystems/` | 레시피, 손님 테이블 관리 |
| `HUD/`, `Widget/` | UI |

## 검증 범위

상호작용, 주문·조리 흐름, 세 가지 실행 모드의 동작은 시연 영상에서 확인할 수 있습니다.
동시 접속자 수나 부하 지표는 따로 측정하지 않았습니다.
