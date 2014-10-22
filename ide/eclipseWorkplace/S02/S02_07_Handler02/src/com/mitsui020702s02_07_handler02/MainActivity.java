package com.mitsui020702s02_07_handler02;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends ActionBarActivity {

	private Button btn;
	private TextView txtView;
	private Handler handler;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        btn=(Button)findViewById(R.id.ButtonId);
        BtnListener btnListener =new BtnListener();
        btn.setOnClickListener(btnListener);
        
        txtView=(TextView)findViewById(R.id.TextViewId);
        
        handler=new MyHandler();
    }

    class BtnListener implements android.view.View.OnClickListener
    {
    	@Override
    	public void onClick(View v) {
    		// TODO Auto-generated method stub
    		NetWorkThread t = new NetWorkThread();
    		t.start();
    	}
    }
    
    class MyHandler extends Handler
    {
    	@Override
    	public void handleMessage(Message msg) {
    		// TODO Auto-generated method stub
    		super.handleMessage(msg);
    		System.out.println("handleMessage----->"+Thread.currentThread().getName());
    		String s=(String)msg.obj;
    		//这样就可以在主线程中设置UI了，解决了上一节的问题
    		txtView.setText(s);
    	}
    }
    
    class NetWorkThread extends Thread
    {
    	@Override
    	public void run() {
    		
    		super.run();
    		System.out.println("NetWorkThread----->"+Thread.currentThread().getName());
    		//模拟访问网络，所以当线程运行时，首先休眠2秒钟
    		
    		try {
				Thread.sleep(2*1000);//直接写这一行，然后在错误中自动添加
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    		//变量s的值，模拟从网络环境中获取的数据(假设s是从网络获取的值)
    		String s= "从网络环境中获取的值";
    		//记住下面这种写法是错误的,详见S02_06_Handler01,此线程是Worker Thread
    		//txtView.setText(s);
    		Message msg=handler.obtainMessage();
    		msg.obj=s;
    		//sendMessage(msg)方法，无论在主线程还是在Worker Thread发送，都是可以的
    		handler.sendMessage(msg);
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
