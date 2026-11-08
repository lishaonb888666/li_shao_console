#include <jni.h>
#include <string>
#include <zygisk.hpp>

using zygisk::Api;
using zygisk::AppSpecializeArgs;

class LiShaoModule : public zygisk::ModuleBase {
public:
    void onLoad(Api *api, JNIEnv *env) override {
        this->api = api;
        this->env = env;
    }

    void preAppSpecialize(AppSpecializeArgs *args) override {
        const char *process = env->GetStringUTFChars(args->nice_name, nullptr);
        std::string pkg(process);
        env->ReleaseStringUTFChars(args->nice_name, process);

        isTarget = (pkg == "com.tencent.tmgp.dfm");
    }

    void postAppSpecialize(const AppSpecializeArgs *) override {
        if (!isTarget) return;

        jclass buildClass = env->FindClass("android/os/Build");
        if (buildClass) {
            auto setField = [&](const char* fieldName, const char* value) {
                jfieldID fieldId = env->GetStaticFieldID(buildClass, fieldName, "Ljava/lang/String;");
                if (fieldId) {
                    jstring jValue = env->NewStringUTF(value);
                    env->SetStaticObjectField(buildClass, fieldId, jValue);
                    env->DeleteLocalRef(jValue);
                }
            };
            
            setField("MODEL", "V2509A");
            setField("BRAND", "iQOO");
            setField("MANUFACTURER", "iQOO");
            setField("DEVICE", "V2509A");
        }
    }

private:
    Api *api;
    JNIEnv *env;
    bool isTarget = false;
};

REGISTER_ZYGISK_MODULE(LiShaoModule)
