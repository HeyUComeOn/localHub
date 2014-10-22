package com.mitsui0212.s02_12_getandpost;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;


public class MainActivity extends ActionBarActivity {

	private EditText editText1;
	private EditText editText2;
	private Button Btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        Btn=(Button)findViewById(R.id.button1);
        editText1=(EditText)findViewById(R.id.editText1);
        editText2=(EditText)findViewById(R.id.editText2);
        
        Btn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String name=editText1.getText().toString();
				String password=editText2.getText().toString();
				
				//使用Get方法向服务器发送请求
				getThread gt=new getThread(name, password);
				gt.start();
				
				//使用Post方法向服务器发送请求
				/*postThread pt=new postThread(name,password);
				pt.start();*/
			}
		});
    }

    class getThread extends Thread
    {
    	String name;
    	String password;
    	public getThread(String name,String password) {
			this.name=name;
			this.password=password;
		}
    	@Override
    	public void run() {
    		// TODO Auto-generated method stub
    		super.run();
    		HttpClient httpClient=new DefaultHttpClient();
    		String url="http://192.168.1.100:8080/s02_12.jsp?"+"name="+name+"&password="+password;
    		HttpGet httpGet=new HttpGet(url);
    		try {
				HttpResponse response=httpClient.execute(httpGet);
				if(response.getStatusLine().getStatusCode()==200)
				{
					HttpEntity entity=response.getEntity();
					BufferedReader reader=new BufferedReader(new InputStreamReader(entity.getContent()));
					String str=reader.readLine();
					Log.d("HTTP", "GET:"+str);
				}
			} 
			catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    	}
    }
    
    class postThread extends Thread
    {
    	String name;
    	String password;
    	
    	public postThread(String name,String password) {
			this.name=name;
			this.password=password;
		}
    	
    	@Override
    	public void run() {
    		// TODO Auto-generated method stub
    		super.run();
    		HttpClient httpClient=new DefaultHttpClient();
    		String url="http://192.168.1.100:8080/s02_12.jsp";
    		//生成使用post方法的使用对象
    		HttpPost httpPost=new HttpPost(url);
    		//NameValuePair代表了一个可以发往服务器的键值对
    		NameValuePair pair1=new BasicNameValuePair("name", name);
    		NameValuePair pair2=new BasicNameValuePair("password", password);
    		//将准备好的一个键值对放置在一个list当中
    		ArrayList<NameValuePair> pairs=new ArrayList<NameValuePair> ();
    		pairs.add(pair1);
    		pairs.add(pair2);
    		//创建代表请求体的对象
    		try {
				HttpEntity requestEntity=new UrlEncodedFormEntity(pairs);
				//将请求体放置在请求对象之中
				httpPost.setEntity(requestEntity);
				//执行请求对象
				try {
					HttpResponse response=httpClient.execute(httpPost);
					if(response.getStatusLine().getStatusCode()==200)
					{
						HttpEntity entity=response.getEntity();
						BufferedReader reader=new BufferedReader(new InputStreamReader(entity.getContent()));
						String str=reader.readLine();
						Log.d("HTTP", "POST:"+str);
					}
				} 
				catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			} catch (UnsupportedEncodingException e) {
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
