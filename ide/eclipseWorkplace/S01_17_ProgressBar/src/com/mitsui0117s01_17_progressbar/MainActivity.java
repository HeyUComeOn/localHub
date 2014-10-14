package com.mitsui0117s01_17_progressbar;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ProgressBar;


public class MainActivity extends ActionBarActivity {

	private ProgressBar progressBar;
	private Button button1;
	private Button button2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        progressBar=(ProgressBar)findViewById(R.id.firstProgressBar);
        button1=(Button)findViewById(R.id.Button1);
        button2=(Button)findViewById(R.id.Button2);
        
        //覆盖xml中的属性
        progressBar.setMax(260);
        progressBar.setProgress(20);
        progressBar.setSecondaryProgress(50);
        
        //
        
        //判断是否为圆形进度条
        boolean flag = progressBar.isIndeterminate();
        
        OnclickListener onclickListener=new OnclickListener();
        button1.setOnClickListener(onclickListener);
        button2.setOnClickListener(onclickListener);
    }


    class OnclickListener implements OnClickListener
    {
    	@Override
    	public void onClick(View v) {
    		// TODO Auto-generated method stub
    		switch(v.getId())
    		{
    		case R.id.Button1:
    			progressBar.incrementProgressBy(10);
    			break;
    		case R.id.Button2:
    			progressBar.incrementSecondaryProgressBy(20);
    			break;
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
