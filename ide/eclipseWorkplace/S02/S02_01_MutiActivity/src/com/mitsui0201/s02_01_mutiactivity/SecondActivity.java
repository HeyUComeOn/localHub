package com.mitsui0201.s02_01_mutiactivity;



import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class SecondActivity extends Activity {

	private Button btn;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.second);
		
		btn=(Button)findViewById(R.id.BUTTON1);
        
        OnclickListener onclickLisener =new OnclickListener();
        btn.setOnClickListener(onclickLisener);
	}
	
	class OnclickListener implements OnClickListener
    {
    	@Override
    	public void onClick(View v) {
    		// TODO Auto-generated method stub
    		Intent intent =new Intent();
    		
    		//intent.setClass(packageContext, cls)
    		//参数一是Context类，Activity是Context类的子类
    		//第一参数不能写this，因为它代表OnclickListener的对象
    		intent.setClass(SecondActivity.this, ThirdActivity.class);
    		startActivity(intent);
    	}
    }
}
