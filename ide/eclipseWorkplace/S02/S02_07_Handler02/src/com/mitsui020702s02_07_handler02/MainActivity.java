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
    		//�����Ϳ��������߳�������UI�ˣ��������һ�ڵ�����
    		txtView.setText(s);
    	}
    }
    
    class NetWorkThread extends Thread
    {
    	@Override
    	public void run() {
    		
    		super.run();
    		System.out.println("NetWorkThread----->"+Thread.currentThread().getName());
    		//ģ��������磬���Ե��߳�����ʱ����������2����
    		
    		try {
				Thread.sleep(2*1000);//ֱ��д��һ�У�Ȼ���ڴ������Զ����
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    		//����s��ֵ��ģ������绷���л�ȡ������(����s�Ǵ������ȡ��ֵ)
    		String s= "�����绷���л�ȡ��ֵ";
    		//��ס��������д���Ǵ����,���S02_06_Handler01,���߳���Worker Thread
    		//txtView.setText(s);
    		Message msg=handler.obtainMessage();
    		msg.obj=s;
    		//sendMessage(msg)���������������̻߳�����Worker Thread���ͣ����ǿ��Ե�
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
