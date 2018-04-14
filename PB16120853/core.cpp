


#ifdef DEBUG
// for unit test
int main() {
	// todo: random
	FILE* file = NULL;
	const long long test_num = 1000000;
	const long long test_groups = 100;
    for (long long  i = 0; i<test_num; i++) {
		if(i%(test_num/test_groups)==0){
			stringstream ss;
			ss << "test" << i / (test_num / test_groups) << ".py";
			if (file) fclose(file);
			file = fopen(ss.str().c_str(), "w");
		}
        string que, ans;
        generate(que, ans);
		fprintf(file,"assert(%lld>=0 and abs((%s)-(%s))<5e-2)\n",i,que.c_str(),ans.c_str());
    }
	fclose(file);
    return 0;
}
#else
int main(){
    for (long long  i = 0; i<2000; i++) {
        string que, ans;
        generate(que, ans);
        cout<<que<<" = "<<ans<<endl;
    }
    return 0;
}
#endif