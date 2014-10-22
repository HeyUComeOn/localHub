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
			
			//在一个应用程序中，主线程通常用于接收用户的输入，以及运算的结果返回给用户
			//对于一些可能会产生阻塞的操作，必须放置在Worker Thread中
			//A(pplication) N(ot) R(esposible)
			try {
				Thread.sleep(10*1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			//子线程
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
				//textView.setText("来自子线程的修改");绝大多数情况下不允许在子线程修改UI的，ProgressBar可以
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
