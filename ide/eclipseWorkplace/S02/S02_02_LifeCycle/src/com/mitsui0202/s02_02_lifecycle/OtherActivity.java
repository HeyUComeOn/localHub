package com.mitsui0202.s02_02_lifecycle;

import android.app.Activity;
import android.os.Bundle;

public class OtherActivity extends Activity {

	//在Activity第一次被创建时调用
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        System.out.println("xxx___OtherActivity onCreate !-->在Activity第一次被创建时");
    }
    
    //当Activity变得可见时调用这个函数
    @Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
        System.out.println("xxx___OtherActivity onStart !-->当Activity变得可见时");

	}

    //当Activity准备与用户交互时调用这个函数
    @Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
        System.out.println("xxx___OtherActivity onResume !-->当Activity准备与用户交互时");

	}

    //当系统即将启动另一个Activity时调用这个函数
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
        System.out.println("xxx___OtherActivity onPause !-->当系统即将启动另一个Activity时");

	}

	//当前Activity变得不可见时调用这个函数
	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
        System.out.println("xxx___OtherActivity onStop !-->当前Activity变得不可见时");

	}

	//当前Activity被销毁之前调用这个函数
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
        System.out.println("xxx___OtherActivity onDestroy !-->当前Activity被销毁之前");

	}
	
	//当这个Activity再次启用之前调用这个函数
	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
        System.out.println("xxx___OtherActivity onRestart !-->这个Activity再次启用");

	}

}
