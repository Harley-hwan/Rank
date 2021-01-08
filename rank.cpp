#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct list {
	string name; // 이름
	vector<int> v; // 각 제출한 보고서의 점수
};
bool operator<(list a, list b) { // 우선순위 큐의 정렬 우선순위 부여를 위해 구현된 비멤버 연산자 operator
	// 아래 조건으로 자동으로 정렬됩니다
	int a_size = a.v.size(), b_size = b.v.size(); // 비교할 두 리스트 a와 b의 크기 저장
	if (a_size == b_size) { // 크기가 같다면 
		int a_sum = 0; // 보고서 점수의 합
		int b_sum = 0;
		for (int i = 0; i < a_size; i++) {
			a_sum += a.v[i]; // 합 계산
			b_sum += b.v[i];
		}
		if (a_sum == b_sum) { // 두 사람의 보고서 점수 합이 같다면, 최저 점수로 비교
			int last = 0; // 비교 시작 인덱스 ( 각 리스트의 벡터는 오름차순으로 정렬되어있기 때문에
			
			while (last < a_size) { // 배열 사이즈만큼 반복
				if (a.v[last] == b.v[last]) { // 점수가 같다면 계속 비교
					last++;
				}
				else {
					return (a.v[last] < b.v[last]); // 규칙 4, 최저점이 큰 것 우선
				}
			}

			// 여기까지 왔다는 것은 크기, 점수, 최저점들의 비교가 전부 같은 상태입니다.
			a_sum -= a.v[0]; // 최저점 뺌
			a_sum -= a.v[a_size - 1]; // 최고점 뺌
			a_sum = max(a_sum, 0); 	// 합에서 최저와 최고 점수를 뺀 나머지의 합 , 만약 제출한 레폿이 1개라면 중복적으로 값이 빼짐. 
									// 0보다 작아지므로 이런 경우를 위해 최소 0으로 설정
			
			b_sum -= b.v[0];
			b_sum -= b.v[b_size - 1];
			b_sum = max(b_sum, 0); 
			if (a_sum == b_sum) {
				return a.name > b.name; // 규칙 6, 다 같다면 이름 순으로 우선순위 부여
			}
			return (a_sum < b_sum); // 규칙 3, 합이 더 큰사람에게 높은 우선순위 부여
		}
		return (a_sum < b_sum); // 규칙 2, 점수의 합이 더 큰사람에게 높은 우선순위 부여
	}
	return (a.v.size() < b.v.size()); // 규칙 1, 제출 개수가 더 많은 사람을 더 높은 우선순위 부여
}
int main() {
	// 이 문제는 정렬 기준을 통해 누가 우선순위를 더 높게 부여 받아야하는지 구현하는 문제입니다.
	int n;
	cin >> n;
	priority_queue<list, vector<list> > pq; // 우선순위 큐는 부여된 우선순위가 높은 순서대로 출력됩니다.
	for (int i = 0; i < n; i++) {
		list tmp; // 각 사람들의 실험과목 보고서 점수를 저장하기 위한 리스트 구조체입니다.
		cin >> tmp.name;
		while (1) {
			int num;
			cin >> num;
			if (num == 0)break; // 0 까지 입력
			tmp.v.push_back(num); // 리스트의 벡터에 각 점수들 저장
		}
		sort(tmp.v.begin(), tmp.v.end()); // 조건에 최저, 최고 점수에 대한 규칙이 존재하므로 오름차순 정렬해줍니다.
		pq.push(tmp); // 우선순위에 넣어주게되면 operator 연산자를 통해 자동으로 우선순위를 찾아 정렬됩니다.
	}
	while (!pq.empty()) { // 출력
		cout << pq.top().name << "\n";
		pq.pop();
	}
}