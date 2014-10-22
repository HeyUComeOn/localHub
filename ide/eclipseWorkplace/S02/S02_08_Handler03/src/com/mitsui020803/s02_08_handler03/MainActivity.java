package com.mitsui020803.s02_08_handler03;



import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
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
        
        WorkerThread t=new WorkerThread();
        t.start();
    }


    class BtnListener implements android.view.View.OnClickListener
    {
    	@Override
    	public void onClick(View v) {
    		System.out.println("onClick----->"+Thread.currentThread().getName());
    		Message msg=handler.obtainMessage();
    		handler.sendMessage(msg);
    		
    		
    	}
    }
    
    class MyHandler extends Handler
    {
    	@Override
    	public void handleMessage(Message msg) {
    		// TODO Auto-generated method stub
    		super.handleMessage(msg);
    		System.out.println("handleMessage----->"+Thread.currentThread().getName());
    		System.out.println("�յ�����Ϣ����");
    		
    	}
    }
    
    class WorkerThread extends Thread
    {
    	@Override
    	public void run() {
    		
    		super.run();
    		//׼��Looper����
    		Looper.prepare();
    		//��WorkerThread������һ��Handler����
    		handler=new MyHandler();
    		//������loop()����֮��Looper���󽫲��ϵش���Ϣ���е���ȡ����Ϣ����Ȼ�����handler��handleMessage�����������Ϣ����
    		//�����Ϣ���е���û����Ϣ��������߳�����
    		Looper.loop();
    		
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
