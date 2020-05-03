/*
 * first lets remove every interval lies in another interval and subtract the number of removed intervals from k 
 * now lets sort the intervals ( notice that both the li & ri are in increasing order ) 
 * lets fill dp [N][K][2] , dp[i][j][z] is the maximum amount of time covered by the the first i cows and we have fired j cows and z = 0 the i'th cow is fired z = 1 otherwise 
 * it is easy to fill the dp[i][j][0] part -> dp [i][j][0] = max ( dp [i-1][j-1][0] , dp [i-1][j-1][1] ) 
 * so we are remaining with the part of not firing the i'th cow , notice that between all of the id that achieve r[id] > l[i] 
 * the optimal solution is to take the minimum id ( the minimum intersection ) , let J = max ( 0 , j - ( i - id - 1 ) ) then -> 
 * dp [i][j][1] = ( max  dp [id][J][0] firing all the cows that intersect with the i'th cow  
 * dp [id][J][1] - overlap ( id , i ) firing all the cows the intersect with the i'th cow expect the cow with the minimum intersection ) 
 * + the size of the i'th interval ( dont forget to subtract the overlap between the i'th cow and the id cow when trying not to fire it ) 
*/ 
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
int N , n , k ;
int done [100009] ;
vpi ord ;
pi a [100009] , ret [100009] ;
int dp [100009][109][2] ;
int sz ( int l , int r ) {
	return r - l ;
}
int overlap ( int i , int j ) {
	return max ( 0 , a [i].se - a [j].fi ) ;
}
int find ( int l , int r ) {
	int id = lb ( ord.begin() , ord.end() , mp ( l , -1 ) ) - ord.begin() ;
	if ( ord [id] .fi == r ) id -- ;
	return id ;
}
int main () {
	freopen("lifeguards.in", "r", stdin);
	freopen("lifeguards.out", "w", stdout);
	cin >> n >> k ;
	for ( int i = 0 ; i < n ; i ++ ) {
		cin >> ret [i] .fi >> ret [i] .se ;
	}
	sort ( ret , ret + n ) ;
	int Mx = 0 ;
	for ( int i = 0 ; i < n ; i ++ ) {
		done [i] = ( Mx > ret [i] .se ) ;
		Mx = max ( Mx , ret[i] .se ) ;
	}
	a [0] = { 0 , 0 } ;
	ord .pb (a[0]) ;
	for ( int i = 0 ; i < n ; i ++ ) {
		if ( done [i] ) C ;
		a [ ++N ] = ret [i] ; 
		ord .pb ( { ret [i].se , ret [i].fi } ) ;
	}  
	k -= ( n - N ) ;
	k = max ( k , 0 ) ;
	for ( int i = 1 ; i <= N ; i ++ ) {
		int id = find ( a[i] .fi , a[i] .se ) ;
		for ( int j = 0 ; j <= min ( k , i ) ; j ++ ) {
			if ( j ) dp [i][j][0] = max ( dp [i-1][j-1][0] , dp [i-1][j-1][1] ) ;
			if ( j == i ) break ; 
			int J = max ( 0 , j - ( i - id - 1 ) ) ;
			dp [i][j][1] = max ( dp [id][J][0] , dp [id][J][1] - overlap ( id , i ) ) + sz ( a[i] .fi , a[i] .se ) ;
		}
	}
	cout << max ( dp [N][k][0] , dp [N][k][1] ) << endl ;
}
