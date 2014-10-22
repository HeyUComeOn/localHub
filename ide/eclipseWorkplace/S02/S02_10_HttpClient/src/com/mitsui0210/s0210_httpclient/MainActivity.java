package com.mitsui0210.s0210_httpclient;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import org.apache.http.Header;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;


public class MainActivity extends ActionBarActivity {

	private Button Btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        Btn=(Button)findViewById(R.id.button1);
        
        Btn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// ԭ�����̵߳��в�����������磨����״���ܲ��ȶ���������������
				NetWorkThread t=new NetWorkThread();
				t.start();
			}
		});
    }

    class NetWorkThread extends Thread
    {
    	@Override
    	public void run() {
    		// TODO Auto-generated method stub
    		super.run();
    		//����HttpClient
    		HttpClient httpClient=new DefaultHttpClient();
    		//������������Ķ���,�����Ƿ��ʵķ�������ַ"http://www.marschen.com/data1.html"
    		HttpGet httpGet=new HttpGet("http://www.marschen.com/data1.html");
    		//ע��˴�����Ϊ��ӡ�����ͷ������������Զ����
    		httpGet.addHeader("Accept-Language", "zh-CN,zh;q=0.8");
    		Header []reqHeaders=httpGet.getAllHeaders();
    		for (int i = 0; i < reqHeaders.length; i++) {
    			String Name=reqHeaders[i].getName();
    			String Value=reqHeaders[i].getValue();
    			Log.d("HTTP", "reqHeaders : Name:"+Name+"Value"+Value);
			}
    		//ִ�����󣬻�ȡ��������������Ӧ����``
    		try {
				HttpResponse httpResponse=httpClient.execute(httpGet);
				Header []respHeaders=httpResponse.getAllHeaders();
	    		for (int i = 0; i < respHeaders.length; i++) {
	    			String Name=respHeaders[i].getName();
	    			String Value=respHeaders[i].getValue();
	    			Log.d("HTTP", "respHeaders : Name:"+Name+"Value"+Value);
	    		}
				//�����Ӧ��״̬�Ƿ�����(�Ƿ�Ϊ200)
				int code=httpResponse.getStatusLine().getStatusCode();
				if(code==200)
				{//����Ӧ������ȡ������
					HttpEntity entity=httpResponse.getEntity();
					InputStream in=entity.getContent();
					BufferedReader reader=new BufferedReader(new InputStreamReader(in));
					String line=reader.readLine();
					
					Log.d("HTTP", "�ӷ�����ȡ�õ�����Ϊ"+line);
				}
			
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
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
