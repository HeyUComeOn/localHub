package com.mitsui0205.s02_05_thread01;

import android.support.v7.app.ActionBarActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

public class MainActivity extends ActionBarActivity {

	private ProgressBar progressBar1;
	private Button btn;
	private TextView textView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		btn = (Button) findViewById(R.id.Button);
		textView = (TextView) findViewById(R.id.TextView);
		progressBar1 = (ProgressBar) findViewById(R.id.progressBar1);

		OnclickListener listener = new OnclickListener();
		btn.setOnClickListener(listener);
	}

	class OnclickListener implements android.view.View.OnClickListener {
		public void onClick(android.view.View v) {
			
			//��һ��Ӧ�ó����У����߳�ͨ�����ڽ����û������룬�Լ�����Ľ�����ظ��û�
			//����һЩ���ܻ���������Ĳ��������������Worker Thread��
			//A(pplication) N(ot) R(esposible)
			try {
				Thread.sleep(10*1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			//���߳�
			MyThread thread = new MyThread();
			thread.start();
		};
	}

	
	class MyThread extends Thread {
		@Override
		public void run() {

			super.run();
			for (int i = 0; i < 100; i++) {
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				//textView.setText("�������̵߳��޸�");�����������²����������߳��޸�UI�ģ�ProgressBar����
				progressBar1.setProgress(progressBar1.getProgress()+1);
			}

		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
