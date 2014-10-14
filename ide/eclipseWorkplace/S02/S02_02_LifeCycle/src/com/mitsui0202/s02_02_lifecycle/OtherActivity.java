package com.mitsui0202.s02_02_lifecycle;

import android.app.Activity;
import android.os.Bundle;

public class OtherActivity extends Activity {

	//��Activity��һ�α�����ʱ����
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        System.out.println("xxx___OtherActivity onCreate !-->��Activity��һ�α�����ʱ");
    }
    
    //��Activity��ÿɼ�ʱ�����������
    @Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
        System.out.println("xxx___OtherActivity onStart !-->��Activity��ÿɼ�ʱ");

	}

    //��Activity׼�����û�����ʱ�����������
    @Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
        System.out.println("xxx___OtherActivity onResume !-->��Activity׼�����û�����ʱ");

	}

    //��ϵͳ����������һ��Activityʱ�����������
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
        System.out.println("xxx___OtherActivity onPause !-->��ϵͳ����������һ��Activityʱ");

	}

	//��ǰActivity��ò��ɼ�ʱ�����������
	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
        System.out.println("xxx___OtherActivity onStop !-->��ǰActivity��ò��ɼ�ʱ");

	}

	//��ǰActivity������֮ǰ�����������
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
        System.out.println("xxx___OtherActivity onDestroy !-->��ǰActivity������֮ǰ");

	}
	
	//�����Activity�ٴ�����֮ǰ�����������
	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
        System.out.println("xxx___OtherActivity onRestart !-->���Activity�ٴ�����");

	}

}
