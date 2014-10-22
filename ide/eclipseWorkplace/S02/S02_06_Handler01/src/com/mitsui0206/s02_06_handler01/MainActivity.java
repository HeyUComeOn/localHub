package com.mitsui0206.s02_06_handler01;

import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;


public class MainActivity extends ActionBarActivity {

	private Button btn;
	private Handler handler;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        btn=(Button)findViewById(R.id.Button);
        ButtonListener lis =new ButtonListener();
        btn.setOnClickListener(lis);
        
        handler=new FirstHandler();
    }


    class ButtonListener implements android.view.View.OnClickListener
    {
    	@Override
    	public void onClick(View v) {
    		// 当用户点击按钮时，我们创建一个消息对象，并使用handler发送该对象
    		Message message=handler.obtainMessage();
    		message.what=2;
    		handler.sendMessage(message);//发送到消息队列当中去
    		//1、Looper将会从消息队列中将消息对象取出
    		//2、Looper将会找到与消息对象对应的Handler对象
    		//3、Looper将会调用此Handler对象的handleMessage(Message msg)方法用于处理消息对象
    	}
    }
    
    class FirstHandler extends Handler
    {
    	@Override
    	public void handleMessage(Message msg) {
    		// TODO Auto-generated method stub
    		super.handleMessage(msg);
    		int what=msg.what;
    		System.out.println("xxx___"+what);
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
