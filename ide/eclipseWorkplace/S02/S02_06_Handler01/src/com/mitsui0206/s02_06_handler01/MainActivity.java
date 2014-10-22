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
    		// ���û������ťʱ�����Ǵ���һ����Ϣ���󣬲�ʹ��handler���͸ö���
    		Message message=handler.obtainMessage();
    		message.what=2;
    		handler.sendMessage(message);//���͵���Ϣ���е���ȥ
    		//1��Looper�������Ϣ�����н���Ϣ����ȡ��
    		//2��Looper�����ҵ�����Ϣ�����Ӧ��Handler����
    		//3��Looper������ô�Handler�����handleMessage(Message msg)�������ڴ�����Ϣ����
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
