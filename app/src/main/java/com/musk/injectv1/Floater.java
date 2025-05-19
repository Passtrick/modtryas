package com.musk.injectv1;

import android.animation.ArgbEvaluator;
import android.animation.TimeAnimator;
import android.animation.ValueAnimator;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.AlertDialog;
import android.app.Service;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.graphics.Typeface;
import android.graphics.drawable.Animatable;
import android.graphics.drawable.GradientDrawable;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.text.Html;
import android.text.InputFilter;
import android.text.InputType;
import android.text.method.DigitsKeyListener;
import android.util.Base64;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.TextView;
import android.app.Dialog;
import android.content.Intent;
import android.graphics.drawable.ColorDrawable;
import android.os.AsyncTask;
import android.widget.ProgressBar;
import android.widget.Toast;

import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.io.File;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;


import static android.view.ViewGroup.LayoutParams.WRAP_CONTENT;
import static android.view.ViewGroup.LayoutParams.MATCH_PARENT;
import static android.widget.RelativeLayout.ALIGN_PARENT_RIGHT;
import static java.lang.System.exit;
import java.util.UUID;
import android.content.Context;
import android.annotation.SuppressLint;
import android.provider.Settings;
import java.util.Timer;
import java.lang.ref.WeakReference;
import java.io.InputStream;
import android.graphics.drawable.Drawable;
import java.io.IOException;
import com.topjohnwu.superuser.Shell;
import android.graphics.Canvas;

public class Floater extends Service {

	private ESPView overlayView;
	
    public static boolean isInjected = false;

	public GradientDrawable botGradInj;
	public WindowManager mEspWindowManager;
	
	public static native void DrawOn(ESPView espView, Canvas canvas);

	
	private WindowManager.LayoutParams espParams;
	
    
	public static String pkg = "com.kiloo.subwaysurf";

	public static final String random = UUID.randomUUID().toString();

	private final int BTN_BG_STROKE = Color.parseColor("RED");

	public GradientDrawable gdMenuBody;

    public String DATE_FORMAT = "yyyy-MM-dd HH:mm:ss";

	private String EVENT_DATE_TIME = "2021-12-31 10:30:00";

	private final int MENU_BG_COLOR = Color.parseColor("BLACK");

	private final int MENU_BG_STROKE = Color.parseColor("RED");

	private final float MENU_CORNER = 8.0f;

	public final int MENU_WIDTH = 200;

	private final int TEXT_COLOR = Color.parseColor("#DEEDF6");

    public Button close;

    public String expire = "DTEXPIRE";

	public LinearLayout header;
	public LinearLayout patches;

	public TextView valiD;
	public Button inject;

	public static native String Title2();

	public native String Title();

	public native String Heading();

	public RelativeLayout mCollapsed;

	public LinearLayout mExpanded;

	public RelativeLayout mRootContainer;

	public WindowManager mWindowManager;

	public WindowManager.LayoutParams params;

	public FrameLayout rootFrame;

	public Runnable runnable;
    public ScrollView scrollView;
	
	private MediaPlayer FXPlayer;
    public View mFloatingView;
        private Button kill;
    private LinearLayout mButtonPanel;
        public LinearLayout mSettings;
       private LinearLayout view1;
    private LinearLayout view2;
    private AlertDialog alert;
    private EditText edittextvalue;
       private static final String TAG = "Mod Menu";
    
    


    public ImageView startimage;


		public Drawable mImage;

	@Override
    public IBinder onBind(Intent intent) {
        return null;
    }

	public native void Changes(int feature, int value);

    private native String[] getFeatureList();



    @Override
public void onCreate() {
    super.onCreate();
    
    // Agregar aquí la inicialización de Shell
    Shell.setDefaultBuilder(Shell.Builder.create()
        .setFlags(Shell.FLAG_REDIRECT_STDERR)
        .setTimeout(10));
    
    initFloatingViewService();
    
    this.overlayView = new ESPView((Context)this);
    
    DrawCanvas();
    
    final Handler handler = new Handler();
    handler.post(new Runnable() {
        public void run() {
            Thread();
            handler.postDelayed(this, 1000);
        }
    });
}

	public void Thread() {
        if (this.rootFrame != null) {
        }
    }
	private int getLayoutType() {
        if (Build.VERSION.SDK_INT >= 26) {
            return 2038;
        }
        if (Build.VERSION.SDK_INT >= 24) {
            return 2002;
        }
        return Build.VERSION.SDK_INT >= 23 ? 2005 : 2003;
    }
	

	private void DrawCanvas() {



        WindowManager.LayoutParams layoutParams;
        this.espParams = layoutParams = new WindowManager.LayoutParams( getLayoutType(), 1080, -3);
        layoutParams.gravity = Gravity.TOP | Gravity.START;
        this.espParams.x = 0;
        this.espParams.y = 100;
        this.mWindowManager.addView((View)this.overlayView, (ViewGroup.LayoutParams)this.espParams);
    }
    private void initFloatingViewService() {  
        this.rootFrame = new FrameLayout((this));

	    this.rootFrame.setOnTouchListener(onTouchListener());

		this.mRootContainer = new RelativeLayout(this);

		this.mCollapsed = new RelativeLayout(this);

		this.mCollapsed.setVisibility(8);

		this.mExpanded = new LinearLayout(this);

		this.header = new LinearLayout(this);

		LinearLayout view1 = new LinearLayout(this);

		patches = new LinearLayout(this);

		LinearLayout view2 = new LinearLayout(this);

		LinearLayout mButtonPanel = new LinearLayout(this);

		this.startimage = new ImageView(this);

		this.startimage.setLayoutParams(new RelativeLayout.LayoutParams(-2, -2));

		int applyDimension = (int) TypedValue.applyDimension(1, 50.0f, this.getResources().getDisplayMetrics());

		this.startimage.getLayoutParams().height = applyDimension;

		this.startimage.getLayoutParams().width = applyDimension;

		this.startimage.requestLayout();

		this.startimage.setScaleType(ImageView.ScaleType.FIT_XY);

		byte[] decode = Base64.decode(Title2(), 0);
		this.startimage.setImageBitmap(BitmapFactory.decodeByteArray(decode, 0, decode.length));
        ((ViewGroup.MarginLayoutParams) this.startimage.getLayoutParams()).topMargin = dp2px(10);
        this.startimage.setOnTouchListener(onTouchListener());
        this.startimage.setOnClickListener(new View.OnClickListener() {
				public void onClick(View view) {
					Floater.this.mCollapsed.setVisibility(8);
					Floater.this.mExpanded.setVisibility(0);
				}
			});

	    this.mExpanded.setVisibility(0);
        this.mExpanded.setGravity(17);
        this.mExpanded.setWeightSum(1.0f);
        this.mExpanded.setOrientation(1);
        this.mExpanded.setPadding(m3dp(5), m3dp(5), m3dp(5), m3dp(5));



		this.scrollView = new ScrollView(this);
        this.scrollView.setLayoutParams(new LinearLayout.LayoutParams(-1, m3dp(180)));

		try {
            // get input stream
            InputStream ims = getAssets().open("musk4.jpg");
            // load image as Drawable
            Drawable d = Drawable.createFromStream(ims, null);

			this.gdMenuBody = new GradientDrawable();
			this.gdMenuBody.setCornerRadius(8.0f);
			this.gdMenuBody.setColor(this.MENU_BG_COLOR);
			this.gdMenuBody.setStroke(2, this.MENU_BG_STROKE);
			this.mExpanded.setBackground(gdMenuBody);


			this.scrollView.setBackgroundDrawable(d);

        }
        catch(IOException ex) {
            return;
        }




    	RelativeLayout.LayoutParams layoutExpanded_LayoutParams = new RelativeLayout.LayoutParams(m3dp(200), -2);
        layoutExpanded_LayoutParams.addRule(20, -1);
        layoutExpanded_LayoutParams.addRule(10, -1);

		this.mExpanded.setLayoutParams(layoutExpanded_LayoutParams);

		RelativeLayout relativeLayout2 = new RelativeLayout(this);
        relativeLayout2.setLayoutParams(new RelativeLayout.LayoutParams(-1, -1));
        relativeLayout2.setVerticalGravity(16);

		RelativeLayout.LayoutParams closeparams = new RelativeLayout.LayoutParams(-2, m3dp(30));
        closeparams.setMargins(5, 5, 5, 0);
        closeparams.addRule(9);

		this.close = new Button(this);

		GradientDrawable botGrad = new GradientDrawable();
        botGrad.setStroke(2, this.BTN_BG_STROKE);
        botGrad.setCornerRadius(8.0f);
        this.close.setBackground(botGrad);
		close.setTypeface(Typefaces.get(this , "m.ttf"));
		this.close.setText("CLOSE");
        this.close.setTextSize(13.0f);
        this.close.setPadding(10, 5, 10, 5);
        this.close.setTextColor(Color.parseColor("#D5E3EB"));
        this.close.setLayoutParams(closeparams);
        this.close.setOnClickListener(new View.OnClickListener() {
				public void onClick(View view) {
					Floater.this.mCollapsed.setVisibility(0);
					Floater.this.mExpanded.setVisibility(8);
				}
			});
        RelativeLayout.LayoutParams injectparams = new RelativeLayout.LayoutParams(-2, m3dp(30));
        injectparams.setMargins(5, 5, 5, 0);
        injectparams.addRule(11);

		this.inject = new Button(this);
		this.botGradInj = new GradientDrawable();
        this.botGradInj.setStroke(2, this.BTN_BG_STROKE);
        this.botGradInj.setColor(Color.parseColor("#FF0000"));
        this.inject.setTextColor(Color.parseColor("#D5E3EB"));
        this.botGradInj.setCornerRadius(8.0f);
        this.inject.setBackground(this.botGradInj);
		this.inject.setText("INJECT");
        this.inject.setTextSize(13.0f);
        inject.setTypeface(Typefaces.get(this , "m.ttf"));
		this.inject.setPadding(10, 5, 10, 5);
        this.inject.setLayoutParams(injectparams);
        this.inject.setOnClickListener(new View.OnClickListener() {
				public void onClick(View view) {
					if (!Floater.isInjected) {
					Inject();
				
					}
				}
			});

	    this.rootFrame.setLayoutParams(new FrameLayout.LayoutParams(-1, -1));

		this.mRootContainer.setLayoutParams(new FrameLayout.LayoutParams(-2, -2));

		this.mCollapsed.setLayoutParams(new RelativeLayout.LayoutParams(-2, -2));

		this.header.setLayoutParams(new LinearLayout.LayoutParams(-1, m3dp(60)));

		this.header.setOrientation(1);

		this.header.setGravity(17);

		try {
            // get input stream
            InputStream ims = getAssets().open("head2.jpeg");
            // load image as Drawable
            Drawable d = Drawable.createFromStream(ims, null);
			this.header.setBackgroundDrawable(d);


        }
        catch(IOException ex) {
            return;
        }


		view1.setLayoutParams(new LinearLayout.LayoutParams(-1, 2));
        view1.setBackgroundColor(this.BTN_BG_STROKE);

		patches.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        patches.setOrientation(1);
        patches.setGravity(17);

		view2.setLayoutParams(new LinearLayout.LayoutParams(-1, 2));
        view2.setBackgroundColor(this.BTN_BG_STROKE);

		mButtonPanel.setLayoutParams(new LinearLayout.LayoutParams(-2, -2));

		TextView title = new TextView(this);
        title.setText(Title());
        title.setTextColor(Color.parseColor("GREEN"));
		title.setTypeface(Typefaces.get(this , "m.ttf"));
	    title.setTextSize(18.0f);
        title.setGravity(17);
        title.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));

		this.valiD = new TextView(this);
        this.valiD.setText(Html.fromHtml(Heading()));
		valiD.setTypeface(Typefaces.get(this , "m.ttf"));
		this.valiD.setTextSize(12.0f);
        this.valiD.setGravity(17);
        this.valiD.setTextColor(Color.parseColor("#FF8000"));
        LinearLayout.LayoutParams layoutParams6 = new LinearLayout.LayoutParams(-1, -2);
        layoutParams6.gravity = 17;
        this.valiD.setLayoutParams(layoutParams6);



		this.params = new WindowManager.LayoutParams(-2, -2, Build.VERSION.SDK_INT >= 26 ? 2038 : 2002, 8, -3);

		WindowManager.LayoutParams layoutParams = this.params;
        layoutParams.gravity = 51;
        layoutParams.x = 0;
        layoutParams.y = 100;

		this.rootFrame.addView(this.mRootContainer);

		this.mRootContainer.addView(this.mCollapsed);

		this.mRootContainer.addView(this.mExpanded);

		this.mCollapsed.addView(this.startimage);

		this.mExpanded.addView(this.header);

		this.header.addView(title);

		this.mExpanded.addView(view1);

		this.mExpanded.addView(this.scrollView);
		this.header.addView(this.valiD);

		this.scrollView.addView(patches);

		this.mExpanded.addView(view2);

		relativeLayout2.addView(this.close);

		relativeLayout2.addView(this.inject);

		this.mExpanded.addView(relativeLayout2);

		this.mWindowManager = (WindowManager) this.getSystemService("window");

		this.mWindowManager.addView(this.rootFrame, this.params);

		
		
		
		
		}
		
	private void Musk(){

		ulalalalal("/storage/emulated/0/com.garena.msdk/guest100067.dat");
		ulalalalal("/storage/emulated/0/com.garena.msdk");
		ulalalalal( "/storage/emulated/0/Android/data/com.dts.freefireth/files/reportnew.db");
		ulalalalal("/storage/emulated/0/Android/data/com.dts.freefireth/files/ymrtc_log.txt" );
		ulalalalal( "/storage/emulated/0/Android/data/com.dts.freefireth/files/contentcache"  );
		ulalalalal( "/storage/emulated/0/Android/data/com.dts.freefireth/files/il2cpp");
		ulalalalal("/storage/emulated/0/Android/data/com.dts.freefireth/files/ImageCache");
		ulalalalal( "/data/data/com.dts.freefireth/shared_prefs" );
		ulalalalal("/data/data/com.dts.freefireth/shared_prefs/.xml" );
		ulalalalal(  "/data/data/com.dts.freefireth/shared_prefs/com.google.firebase.messaging.xml");
		ulalalalal("/data/data/com.dts.freefireth/shared_prefs/com.google.firebase.crashlytics.xml");
		ulalalalal("/data/data/com.dts.freefireth/shared_prefs/com.garena.msdk.persist.fallback.xml" );
		ulalalalal( "/data/data/com.dts.freefireth/shared_prefs/com.facebook.sdk.USER_SETTINGS.xml");
		ulalalalal(  "/data/data/com.dts.freefireth/shared_prefs/YoumeCommon.xml");
		ulalalalal(  "/data/data/com.dts.freefireth/shared_prefs/WebViewChromiumPrefs.xml");
		ulalalalal(    "/data/data/com.dts.freefireth/shared_prefs/FreeFireSharedPreference.xml");
		ulalalalal("/data/data/com.dts.freefireth/shared_prefs/com.google.android.gms.measurement.prefs.xml");
		ulalalalal("/data/data/com.dts.freefireth/shared_prefs/com.google.android.gms.appid.xml");
		ulalalalal( "/data/data/com.dts.freefireth/shared_prefs/com.garena.msdk.token_cache.xml");
		ulalalalal("/data/data/com.dts.freefireth/shared_prefs/com.garena.msdk.app_config.xml");
		ulalalalal("/data/data/com.dts.freefireth/shared_prefs/com.facebook.sdk.attributionTracking.xml");
		ulalalalal(  "/data/data/com.dts.freefireth/shared_prefs/com.facebook.internal.MODEL_STORE.xml");
		ulalalalal(  "/data/data/com.dts.freefireth/shared_prefs/com.android.vending.licensing.APKExpansionPolicy.xml" );
		ulalalalal( "/data/data/com.dts.freefireth/shared_prefs/com.facebook.internal.preferences.APP_SETTINGS.xml");
		ulalalalal(    "/data/data/com.dts.freefireth/shared_prefs/com.facebook.sdk.appEventPreferences.xml");
		ulalalalal(  "/data/data/com.dts.freefireth/shared_prefs/com.facebook.internal.preferences.APP_GATEKEEPERS.xml");
		ulalalalal(  "/data/data/com.dts.freefireth/shared_prefs/com.dts.freefireth.v2.playerprefs.xml" );
		ulalalalal("/data/data/com.dts.freefireth/shared_prefs/com.dts.freefireth_preferences.xml");
		Toast.makeText(Floater.this, "Logout and Login to see the changes!", Toast.LENGTH_SHORT).show();
		

	}
	
	public static void ulalalalal(String fileName ) {
        File file = new File(fileName);
		if (file.exists()) {
			file.delete();
			
		}
	}
	

	       private void ModAss() {
     

			String[] listFT = getFeatureList();

			for (int i = 0; i < listFT.length; i++) {
				final int feature = i;
				String str = listFT[i];
				if (str.contains("Toggle_")) {
					addSwitch(str.replace("Toggle_", ""), new InterfaceBool() {
							public void OnWrite(boolean z) {
								Changes(feature, 0);
							}
						});
				} else if (str.contains("SeekBar_")) {
					String[] split = str.split("_");
					addSeekBar(split[1], Integer.parseInt(split[2]), Integer.parseInt(split[3]), new InterfaceInt() {
							public void OnWrite(int i) {
								Changes(feature, i);
							}
						});
				} else if (str.contains("Category_")) {
					addCategory(str.replace("Category_", ""));
				}


	    	}

			
			   addSwitch("RESET GUEST" , new InterfaceBool() {
					   public void OnWrite(boolean z) {
						   Musk();
					   }
				   });
				   
        
    }


    private View.OnTouchListener onTouchListener() {
        return new View.OnTouchListener() {
            final View collapsedView = Floater.this.mCollapsed;
            final View expandedView = Floater.this.mExpanded;
            private float initialTouchX;
            private float initialTouchY;
            private int initialX;
            private int initialY;

            public boolean onTouch(View view, MotionEvent motionEvent) {
                int action = motionEvent.getAction();
                if (action == 0) {
                    this.initialX = Floater.this.params.x;
                    this.initialY = Floater.this.params.y;
                    this.initialTouchX = motionEvent.getRawX();
                    this.initialTouchY = motionEvent.getRawY();
                    return true;
                } else if (action == 1) {
                    int rawX = (int) (motionEvent.getRawX() - this.initialTouchX);
                    int rawY = (int) (motionEvent.getRawY() - this.initialTouchY);
                    if (rawX < 10 && rawY < 10 && Floater.this.isViewCollapsed()) {
                        try {
                            this.collapsedView.setVisibility(8);
                            this.expandedView.setVisibility(0);
						} catch (NullPointerException e) {
                        }
                    }
                    return true;
                } else if (action != 2) {
                    return false;
                } else {
                    Floater.this.params.x = this.initialX + ((int) (motionEvent.getRawX() - this.initialTouchX));
                    Floater.this.params.y = this.initialY + ((int) (motionEvent.getRawY() - this.initialTouchY));
                    Floater.this.mWindowManager.updateViewLayout(Floater.this.rootFrame, Floater.this.params);
                    return true;
                }
            }
        };
    }


    private void addCategory(String text) {
        TextView textView = new TextView(this);
        textView.setText(text);
        textView.setGravity(17);
        textView.setTextSize(14.0f);
        textView.setTextColor(Color.parseColor("WHITE"));
        textView.setTypeface(Typefaces.get(this , "m.ttf"));
		textView.setPadding(10, 5, 0, 5);
        this.patches.addView(textView);
    }




    @SuppressLint("WrongConstant")
    private void addSwitch(String str, final InterfaceBool sww) {
		final Switch switc = new Switch(this);
		Switch sw = switc;
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, -2);
        layoutParams.leftMargin = m1dp(5);
        layoutParams.rightMargin = m1dp(6);
        layoutParams.topMargin = m1dp(5);
        layoutParams.bottomMargin = m1dp(5);
        sw.setText(str);
        sw.setTextColor(Color.WHITE);
        sw.setLayoutParams(layoutParams);
        sw.setTextSize(2, 15.0f);
		sw.setTypeface(Typefaces.get(this , "m.ttf"));
		final GradientDrawable BackgroundCaixa = new GradientDrawable();
        BackgroundCaixa.setShape(0);
        BackgroundCaixa.setColor(Color.parseColor("#A0FF0044"));
        BackgroundCaixa.setCornerRadius((float) m1dp(10));
        BackgroundCaixa.setSize(m1dp(20), m1dp(20));
        BackgroundCaixa.setStroke(m1dp(1), -7829368);
        final GradientDrawable BackgrounSwitch = new GradientDrawable();
        BackgrounSwitch.setShape(0);
        BackgrounSwitch.setColor(-1);
        BackgrounSwitch.setStroke(m1dp(1), -7829368);
        BackgrounSwitch.setCornerRadius((float) m1dp(10));
        BackgrounSwitch.setSize(m1dp(20), m1dp(20));
        sw.setTrackDrawable(BackgroundCaixa);
        sw.setThumbDrawable(BackgrounSwitch);

		switc.setOnClickListener(new View.OnClickListener() {

				private boolean isActive = true;

				public void onClick(View param1View) {
					sww.OnWrite(this.isActive);
					if (this.isActive) {
						switc.setShadowLayer(20.0f, 0.0f, 0.0f, Color.parseColor("#2EE36D"));
						switc.getBackground().setAlpha(200);
						BackgrounSwitch.setColor(Color.GREEN);
						this.isActive = false;
						return;
					}
					this.isActive = true;
					switc.setShadowLayer(12.0f, 0.0f, 0.0f, Color.parseColor("#db4500"));
					BackgrounSwitch.setColor(-1);

				}
			});
        this.patches.addView(switc);
    }

    @SuppressLint("WrongConstant")
    private void addSeekBar(String str, int progress, int max, InterfaceInt sb) {
		LinearLayout linearLayout = new LinearLayout(this);
        linearLayout.setPadding(10, 5, 0, 5);
        linearLayout.setOrientation(1);
        linearLayout.setGravity(17);
        TextView textView = new TextView(this);
        textView.setTextColor(Color.WHITE);
		textView.setTypeface(Typefaces.get(this , "m.ttf"));

		if (str.equals("Aim - Spot")) {
            textView.setText(Html.fromHtml("<font face='monospace'><b>" + str + ": <font color='red'>" + "OFF" + "</b></font>"));
            Object obj = "Cabeça";
        } else if (str.equals("Aim - Fov")) {
            textView.setText(Html.fromHtml("<font face='monospace'><b>" + str + ": <font color='red'>" + "OFF" + "</b></font>"));
            Object obj2 = "LARANJA";
        } else {
            textView.setText(Html.fromHtml("<font face='monospace'><b>" + str + ": <font color='red'>" + "OFF" + "</b></font>"));
            Object obj3 = "";
        }
        SeekBar seekBar = new SeekBar(this);
        seekBar.setPadding(25, 10, 35, 10);
        seekBar.setMax(max);
        seekBar.setProgress(progress);
        seekBar.getThumb().setColorFilter(this.MENU_BG_STROKE, PorterDuff.Mode.SRC_IN);
        seekBar.getProgressDrawable().setColorFilter(this.MENU_BG_STROKE, PorterDuff.Mode.MULTIPLY);

		final int i5 = progress;
        final SeekBar seekBar2 = seekBar;
        final InterfaceInt sb3 = sb;
        final TextView textView2 = textView;
        final String str3 = str;
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

				private String itv;
				public void onStartTrackingTouch(SeekBar seekBar) {
				}

				public void onStopTrackingTouch(SeekBar seekBar) {
				}

				public void onProgressChanged(SeekBar seekBar, int i, boolean z) {
					int i2 = i5;

					if (str3.equals("Aim - Spot")) {
						if (i == 1) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='green'>" + "Head" + "</b></font>"));

							return;
						}else if (i == 2) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='yellow'>" + "Hip" + "</b></font>"));

							return;
						}else if (i == 3) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='blue'>" + "Leg" + "</b></font>"));

							return;
						}else  {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='red'>" + "OFF" + "</b></font>"));

							return;
						}
					}else if(str3.equals("Aim - Fov")){

						if (i <= 120) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='green'>" + "Low :" + i + "</b></font>"));

							return;
						}else if (i <= 240) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='yellow'>" + "Medium :" + i +"</b></font>"));

							return;
						}else if (i <= 360) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='blue'>" + "Full :" + i + "</b></font>"));

							return;
						}else if(i==0) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='red'>" + "OFF" + "</b></font>"));

							return;
						}



					}else if(str3.equals("Aim - Dist")){

						if (i <= 120) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='green'>" + "Near :" + i + "</b></font>"));

							return;
						}else if (i <= 240) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='yellow'>" + "Medium :" + i +"</b></font>"));

							return;
						}else if (i <= 360) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='blue'>" + "Far :" + i + "</b></font>"));

							return;
						}else if (i==0){
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='red'>" + "OFF" + "</b></font>"));

							return;
						}



					}else   if (str3.equals("CHAMS HACK")) {
						if (i == 1) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='green'>" + "Green" + "</b></font>"));

							return;
						}else if (i == 2) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='red'>" + "Red" + "</b></font>"));

							return;
						}else if (i == 3) {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='blue'>" + "Blue" + "</b></font>"));

							return;
						}else if(i==4){
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='white'>" + "White" + "</b></font>"));

							return;
						}else  {
							seekBar2.setProgress(i);
							sb3.OnWrite(i);
							TextView textView = textView2;
							textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color='red'>" + "OFF" + "</b></font>"));

							return;
						}
					} 





					if (i < i2) {
						seekBar2.setProgress(i2);
						sb3.OnWrite(i5);
						TextView textView = textView2;
						textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color=BLACK'>" + i5 + "</b></font>"));

						return;
					}
					sb3.OnWrite(i);
					textView2.setText(Html.fromHtml("<font typeface='features.ttf'><b>" + str3 + ": <font color=BLACK'>" + i + "</b></font>"));

				}
			});

        linearLayout.addView(textView);
        linearLayout.addView(seekBar);
        this.patches.addView(linearLayout);
    }

	
	public int Game(String pkg) {
    try {
        List<String> result = Shell.cmd("pidof " + pkg).exec().getOut();
        if (!result.isEmpty()) {
            return Integer.parseInt(result.get(0));
        }
        return -1;
    } catch (Exception e) {
        Log.e("Floater", "Error getting PID: " + e.getMessage());
        return -1;
    }
}

	
	public Boolean Inject() {
    try {
        String target = "com.kiloo.subwaysurf";
        String injector = getApplicationInfo().nativeLibraryDir + File.separator + "libinject.so";
        String payload_source = getApplicationInfo().nativeLibraryDir + File.separator + "libmusk.so";
        String payload_dest = "/data/local/tmp/libmusk.so";

        // Ejecutar comandos con libsu
        Shell.cmd(
            "chmod 777 " + injector,
            "cp " + payload_source + " " + payload_dest,
            "chmod 777 " + payload_dest
        ).exec();

        // Obtener PID
        List<String> pidResult = Shell.cmd("pidof " + target).exec().getOut();
        if (pidResult.isEmpty()) {
            Toast.makeText(this, "Target process not found", Toast.LENGTH_SHORT).show();
            return false;
        }

        int pid = Integer.parseInt(pidResult.get(0));
        
        // Ejecutar inyección
        Shell.cmd(injector + " " + pid + " " + payload_dest).exec();

        // Limpiar
        Shell.cmd("rm " + payload_dest).exec();

        if (RunnigTask.Init() < 0) {
            Toast.makeText(this, "Injection Failed!", Toast.LENGTH_SHORT).show();
            this.inject.setText("Status: OFF");
            this.inject.setTextColor(Color.parseColor("#848484"));
            this.botGradInj.setColor(Color.parseColor("#3B170B"));
            isInjected = false;
            return false;
        }

        Toast.makeText(this, "Injection Successful", Toast.LENGTH_SHORT).show();
        ModAss();
        this.inject.setText("Status: ON");
        this.inject.setTextColor(Color.parseColor("#848484"));
        this.botGradInj.setColor(Color.parseColor("#3B170B"));
        isInjected = true;
        return true;

    } catch (Exception e) {
        Log.e("Floater", "Injection error: " + e.getMessage());
        Toast.makeText(this, "Injection error: " + e.getMessage(), Toast.LENGTH_SHORT).show();
        return false;
    }
}
	
	
	
	public float dipToPixels() {
        return TypedValue.applyDimension(1, 8.0f, this.getResources().getDisplayMetrics());
    }

    public static String rdStr() {
        return UUID.randomUUID().toString().replace("-", "");
    }

    /* access modifiers changed from: private */
    public String getUniqueId(Context this2) {
        return UUID.nameUUIDFromBytes((getDeviceName() + Settings.Secure.getString(this2.getContentResolver(), "android_id") + Build.HARDWARE).replace(" ", "").getBytes()).toString().replace("-", "");
    }

    private String getDeviceName() {
        String manufacturer = Build.MANUFACTURER;
        String model = Build.MODEL;
        if (model.startsWith(manufacturer)) {
            return model;
        }
        return manufacturer + " " + model;
    }

    public boolean isViewCollapsed() {
        return this.rootFrame == null || this.mCollapsed.getVisibility() == 0;
    }

    /* renamed from: dp */
    private int m3dp(int paramInt) {
        return (int) TypedValue.applyDimension(1, (float) paramInt, this.getResources().getDisplayMetrics());
    }

    private int dp2px(int paramInt) {
        return (int) ((((float) paramInt) * this.getResources().getDisplayMetrics().density) + 0.5f);
    }

    public void Destroy() {
		View view = this.rootFrame;
        if (view != null) {
            this.mWindowManager.removeView(view);
        }


    }
	private int dp(int i) {
        return (int) TypedValue.applyDimension(1, (float) i, getResources().getDisplayMetrics());
    }

    private boolean isNotInGame() {
        ActivityManager.RunningAppProcessInfo runningAppProcessInfo = new ActivityManager.RunningAppProcessInfo();
        ActivityManager.getMyMemoryState(runningAppProcessInfo);
        return runningAppProcessInfo.importance != 100;
    }


    private interface InterfaceBtn {
        void OnWrite();
    } 

    /* renamed from: com.hckinject.FloatingViewService$SB */
    private interface C0019SB {
        void OnWrite(int i);
    }

    /* renamed from: com.hckinject.FloatingViewService$SW */
    private interface C0020SW {
        void OnWrite(boolean z);
    }

    public int m1dp(int paramInt) {
        return (int) TypedValue.applyDimension(1, (float) paramInt, this.getResources().getDisplayMetrics());
    }

    private interface InterfaceInt {
        void OnWrite(int i);
    }

    private interface InterfaceBool {
        void OnWrite(boolean z);
    }

    private interface InterfaceStr {
        void OnWrite(String s);
    }




}





