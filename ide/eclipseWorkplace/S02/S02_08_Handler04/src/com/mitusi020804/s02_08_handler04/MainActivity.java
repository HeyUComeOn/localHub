package com.mitusi020804.s02_08_handler04;

import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

/*
 * private static Message getPostMessage(Runnable r)�÷����������������
 * 1.������һ��Message����2.��r����ֵ��Runnable��callback����
 * ��һ�����⣬��ΰ�һ��Runnable������뵽��Ϣ�����У�
 * ʵ������������һ��Message����Ȼ��r����ֵ��Runnable��callback���ԣ�Ȼ���ڰ�Message�����������Ϣ������
 * �ڶ�������Looperȡ����Я����r�����Message����֮�����Щʲô
 * ȡ��Message����֮�󣬵�����DispatchMessage������Ȼ���ж�Message��callback�����Ƿ�Ϊ�գ���ʱ��callback������ֵ
 * ����ִ����HandleCallback(Message msg)�������ڸ÷�������ִ����msg.callback.run()
 * */
public class MainActivity extends ActionBarActivity {

	private Button Btn;
	private Handler handler=new Handler();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        Btn=(Button)findViewById(R.id.button1);
        //�����ڲ���
        Btn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				TestThread t=new TestThread();
				t.start();
			}
		});
    }
    
    class TestThread extends Thread
    {
    	@Override
    	public void run() {
    		// TODO Auto-generated method stub
    		super.run();
    		//�����ڲ���
    		Runnable r=new Runnable() {
				
				@Override
				public void run() {
					// �������д�ϸ���UI�Ĵ��룬�൱�ڰ���Щ���´���ŵ����߳�������
					String currentThreadName=Thread.currentThread().getName();
					System.out.println("��ǰ�̵߳�����Ϊ��"+currentThreadName);//������Ϊmain
				}
				
			};
			//�˷�����r�����������Ϣ�����С�Looper�������̣߳�����Ϣ������ȡ����r����
			/*
			 * ���ǵĲ²⣺
			 * Thread t=new Thread(r)
			 * t.start();
			 * �����ݲ��ԵĽ��֤���²����
			 * ����Looperȡ��r֮�����ʲô��Դ����Handler.java
			 * */
			handler.post(r);
    	}
    }


   
}
