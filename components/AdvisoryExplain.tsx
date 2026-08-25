"use client";
import { advisory, advisoryLogic } from "@/lib/advisory";
export default function AdvisoryExplain(){
  return (
    <div className="bg-white p-5 rounded-xl border space-y-4">
      <div className="flex justify-between items-start">
        <div><h3 className="font-bold">Sale-Window Decision — Not Just a Chart</h3><p className="text-xs text-gray-500 mt-1">{advisoryLogic}</p></div>
        <div className={`px-3 py-1 rounded-full text-sm font-bold ${advisory.recommendation==="HOLD"?"bg-green-600 text-white":"bg-red-600 text-white"}`}>{advisory.recommendation} {advisory.holdDays} • {advisory.confidence}% confidence</div>
      </div>
      <div className="grid md:grid-cols-2 gap-4">
        <div>
          <div className="text-xs font-semibold mb-2">WHY? (weighted factors)</div>
          <div className="space-y-1.5">
            {advisory.reasons.map(r=>(
              <div key={r.factor} className="flex gap-2 items-center text-xs bg-gray-50 p-2 rounded">
                <span className={`w-2 h-2 rounded-full ${r.direction==="bullish"?"bg-green-500":r.direction==="bearish"?"bg-red-500":"bg-gray-400"}`}></span>
                <span className="flex-1">{r.factor}</span>
                <span className="font-medium">{r.impact}</span>
                <span className="text-gray-400">{r.weight}%</span>
              </div>
            ))}
          </div>
        </div>
        <div className="space-y-3">
          <div className="bg-green-50 border border-green-200 p-3 rounded">
            <div className="text-xs font-semibold text-green-800">MATH (farm-gate net)</div>
            <div className="text-xs mt-1 font-mono leading-5">
              Today ₹{advisory.math.todayPrice}/q → Peak ₹{advisory.math.forecastPeak}/q ({advisory.math.peakDate})<br/>
              Gross +₹{advisory.math.grossGain} − Storage ₹{advisory.math.storageCost} (14d) − Transport ₹{advisory.math.transportCost} = <b>Net +₹{advisory.math.netGain}/q ({advisory.math.netPct}%)</b>
            </div>
            <div className="text-[11px] text-gray-600 mt-1">On 12 MT = +₹{(advisory.math.netGain*120).toLocaleString("en-IN")} extra vs selling today</div>
          </div>
          <div className="bg-amber-50 border border-amber-200 p-3 rounded text-xs">
            <div className="font-semibold text-amber-800">RISK BRAKE — {advisory.risk.level}</div>
            <div className="mt-1">{advisory.risk.brake}</div>
            <div className="mt-1 font-medium">{advisory.risk.autoTrigger}</div>
          </div>
        </div>
      </div>
    </div>
  );
}
